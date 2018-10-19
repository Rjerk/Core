package app;

import java.nio.channels.Channels;
import java.nio.channels.ReadableByteChannel;
import java.io.File;
import java.io.IOException;
import java.io.InputStream;
import java.io.FileOutputStream;
import java.io.ByteArrayInputStream;
import java.io.OutputStreamWriter;
import java.util.List;
import java.util.ArrayList;
import java.util.Collection;
import java.util.concurrent.TimeUnit;
import java.net.URL;
import java.net.HttpURLConnection;
import java.net.InetAddress;
import java.util.Map;

import com.amazonaws.HttpMethod;
import com.amazonaws.SdkClientException;
import com.amazonaws.AmazonWebServiceRequest;
import com.amazonaws.AmazonClientException;
import com.amazonaws.services.s3.AmazonS3Client;
import com.amazonaws.AmazonServiceException;
import com.amazonaws.SdkClientException;
import com.amazonaws.ClientConfiguration;
import com.amazonaws.Protocol;
import com.amazonaws.auth.BasicAWSCredentials;
import com.amazonaws.auth.AWSStaticCredentialsProvider;
import com.amazonaws.client.builder.AwsClientBuilder.EndpointConfiguration;
import com.amazonaws.event.ProgressEvent;
import com.amazonaws.event.ProgressListener;
import com.amazonaws.event.ProgressEventType;
import com.amazonaws.services.s3.AmazonS3;
import com.amazonaws.services.s3.*;
import com.amazonaws.services.s3.AmazonS3ClientBuilder;
import com.amazonaws.services.s3.transfer.*;
import com.amazonaws.services.s3.model.*;

import com.amazonaws.services.s3.model.BucketLifecycleConfiguration.Transition;
import com.amazonaws.services.s3.model.lifecycle.*;
import com.amazonaws.services.s3.transfer.Transfer.TransferState;
import com.amazonaws.util.StringUtils;

import okhttp3.*;
import okhttp3.MultipartBody.Builder;


/**
 * Hello world!
 *
 */
public class App
{

    private static String accessKey = "javasdk-test";
    private static String secretKey = "javasdk-test";

    private static String bucketName = "test";
    private static String sourceKey =  "pom.xml";
    private static String destinationKey = "pom.xml_2";

    private static BasicAWSCredentials credentials = new BasicAWSCredentials(accessKey, secretKey);
    private static ClientConfiguration clientConfig = new ClientConfiguration().withProtocol(Protocol.HTTP);

    private static AmazonS3 conn = AmazonS3ClientBuilder.standard()
                   .withCredentials(new AWSStaticCredentialsProvider(credentials))
                   .withClientConfiguration(clientConfig)
                   .withEndpointConfiguration(new EndpointConfiguration("192.168.2.17:8000", "us"))
                   .build();


    public void multiPartUpload(String bucket_name, String key_name, String filename)
    {
        File file = new File(filename);
        final long contentLength = file.length();
        long partSize = 300 * 1024 * 1024; // 设置分片大小为 30 MB.

        try {
            // 每个分片的上传，都需要取得 ETag 列表，然后每个分片都上传完成后，需要将
           // ETag 列表传给分片完成请求来结束分片传输
            List<PartETag> partETags = new ArrayList<PartETag>();

            // 初始化分片上传请求
            InitiateMultipartUploadRequest initRequest = new InitiateMultipartUploadRequest(bucket_name, key_name);
            InitiateMultipartUploadResult initResponse = conn.initiateMultipartUpload(initRequest);
            long filePosition = 0;
            // 上传文件分片，需要记录每次上传了文件的哪一部分

            for (int i = 1; filePosition < contentLength; i++) {
                // Because the last part could be less than 100 MB, adjust the part size as needed.
                partSize = Math.min(partSize, (contentLength - filePosition));
                System.out.println("\npartNumber: " + i);
                System.out.println("filePosition: " + filePosition);
                System.out.println("partSize: " + partSize);
                System.out.println("upload: " + filePosition);
                ProgressListener prog = new ProgressListener() {
                    private long bytesWritten = 0;
                    private long totalBytes = -1;
                    public void progressChanged(ProgressEvent e)
                    {
                        System.out.println(" --- : " + bytesWritten);
                        long bytes = e.getBytes();
                        ProgressEventType eventType = e.getEventType();
                        switch (eventType) {
                            case TRANSFER_PART_STARTED_EVENT:
                                System.out.println("Start to upload file using multipart......");
                                break;
                            case REQUEST_CONTENT_LENGTH_EVENT:
                                totalBytes = bytes;
                                System.out.println(totalBytes + " bytes in total will be uploaded");
                                break;
                            case REQUEST_BYTE_TRANSFER_EVENT:
                                bytesWritten += bytes;
                                if (totalBytes != -1) {
                                    int percent = (int)(bytesWritten * 100.0 / totalBytes);
                                    System.out.println(bytes + " bytes have been written at this time, upload progress: " + percent + "%");
                                } else {
                                    System.out.println(bytes + " bytes have been written at this time, upload ratio: unknown");
                                }
                                break;
                            case TRANSFER_PART_COMPLETED_EVENT:
                                System.out.println("Succeed Upload, " + bytesWritten + " bytes have been transferred in total");
                                break;
                            case CLIENT_REQUEST_SUCCESS_EVENT:
                                System.out.println("Client Request Success Event");
                                break;
                            case CLIENT_REQUEST_STARTED_EVENT:
                                System.out.println("Client Request Started Event");
                                break;
                            case TRANSFER_FAILED_EVENT:
                                System.out.println("Failed to upload, " + bytesWritten + " bytes have been transferred");
                                break;

                            case HTTP_RESPONSE_STARTED_EVENT:
                                System.out.println("HTTP RESPONSE STARTED EVENT");
                                break;
                            case HTTP_RESPONSE_COMPLETED_EVENT:
                                System.out.println("HTTP RESPONSE COMPLETED EVENT");
                                break;

                            case HTTP_REQUEST_STARTED_EVENT:
                                System.out.println("HTTP REQUEST STARTED EVENT");
                                break;
                            case HTTP_REQUEST_COMPLETED_EVENT:
                                System.out.println("HTTP REQUEST COMPLETE EVENT");
                                break;

                            case TRANSFER_CANCELED_EVENT:
                                System.out.println("Transfer was canceled");
                                break;
                            case TRANSFER_COMPLETED_EVENT:
                                System.out.println("Transfer completed");
                                break;
                            case TRANSFER_PREPARING_EVENT:
                                System.out.println("Transfer preparing");
                                break;

                            case TRANSFER_PART_FAILED_EVENT:
                                System.out.println("Upload Failed");
                                break;
                            default:
                                System.out.println("other events");
                                break;
                        }
                    }
                };
                // 创建请求来上传分片
                UploadPartRequest uploadRequest = new UploadPartRequest()
                        .withBucketName(bucket_name)
                        .withKey(key_name)
                        .withUploadId(initResponse.getUploadId())
                        .withPartNumber(i)
                        .withFileOffset(filePosition)
                        .withFile(file)
                        .withPartSize(partSize);
                uploadRequest.setGeneralProgressListener(prog);

                // 上传分片和对应分片的 ETag 列表
                UploadPartResult uploadResult = conn.uploadPart(uploadRequest);
                partETags.add(uploadResult.getPartETag());

                filePosition += partSize;
            }

            // 完成分片请求
            CompleteMultipartUploadRequest compRequest =
                new CompleteMultipartUploadRequest(bucket_name,
                                                  key_name,
                                                  initResponse.getUploadId(),
                                                  partETags);
            conn.completeMultipartUpload(compRequest);
        }
        catch(AmazonServiceException e) {
            e.printStackTrace();
        }
        catch(SdkClientException e) {
            e.printStackTrace();
        }
    }

    public static void usePresignedURLPutObject() {
        try {
            java.util.Date expiration = new java.util.Date();
            long expTimeMillis = expiration.getTime();
            expTimeMillis += 1000 * 60 * 60; // 以毫秒为单位，设置 1h 后链接失效
            expiration.setTime(expTimeMillis);

            {
                System.out.println("Upload 1: Generating pre-signed URL.");
                GeneratePresignedUrlRequest generatePresignedUrlRequest =
                            new GeneratePresignedUrlRequest("test-new", "啊")
                                            .withMethod(HttpMethod.PUT) // PUT 方法，授权上传
                                            .withExpiration(expiration);

                // 指定标签 test = 1，test 为标签名，1为标签值
                // 文档见 https://forums.aws.amazon.com/thread.jspa?threadID=252054&tstart=0

                // generatePresignedUrlRequest.putCustomRequestHeader(Headers.S3_TAGGING, "test=1");
                // 生成 presigned URL，用该 URL 可以进行该对象的上传
                //

                URL url = conn.generatePresignedUrl(generatePresignedUrlRequest);
                System.out.println("Pre-Signed URL: " + url.toString());

                OkHttpClient ok_http = new OkHttpClient();
                File file = new File("127M");
                RequestBody formBody = new MultipartBody.Builder()
                                           .setType(MultipartBody.FORM)
                                           .addFormDataPart("file", file.getName(),
                                                            RequestBody.create(MediaType.parse("text/plain"), file))
                                           .addFormDataPart("other_field", "other_field_value")
                                           .build();
                Request request = new Request.Builder().url(url.toString()).put(formBody).build();
                Response response = ok_http.newCall(request).execute();
                System.out.println(" --- " + response.message());

                // HttpURLConnection connection = (HttpURLConnection) url.openConnection();
                // connection.setDoOutput(true);
                // connection.setRequestMethod("PUT");
                // OutputStreamWriter out = new OutputStreamWriter(connection.getOutputStream());
                // out.write("This text uploaded as an object via presigned URL.");
                // out.close();

                // 检查 HTTP 响应码
                // connection.getResponseCode();
                // System.out.println("HTTP response code: " + connection.getResponseCode());

                // 确认对象上传成功
                S3Object object = conn.getObject("test-new", "啊");
                System.out.println("Object " + object.getKey() + " created in bucket " + object.getBucketName());
            }

            { // download a object use prisigned url
                System.out.println("Download: Generating pre-signed URL...");
                GeneratePresignedUrlRequest generatePresignedUrlRequest =
                            new GeneratePresignedUrlRequest("test-new", "啊")
                                            .withMethod(HttpMethod.GET)
                                            .withExpiration(expiration);
                URL url = conn.generatePresignedUrl(generatePresignedUrlRequest);
                System.out.println("Pre-Signed URL: " + url.toString());

                OkHttpClient ok_http = new OkHttpClient();
                Request request = new Request.Builder()
                                    .url(url.toString())
                                    .build();

                Response response = ok_http.newCall(request).execute();
                System.out.println(" --- " + response.message());
                if (!response.isSuccessful()) {
                    throw new IOException("Failed to download file:" + response);
                }
                // save file: download_file
                FileOutputStream fos = new FileOutputStream("download_file");
                fos.write(response.body().bytes());
                fos.close();
            }

            {
                System.out.println("Upload 2: Generating pre-signed URL.");
                GeneratePresignedUrlRequest generatePresignedUrlRequest =
                            new GeneratePresignedUrlRequest("test-new", "哦")
                                            .withMethod(HttpMethod.PUT) // PUT 方法，授权上传
                                            .withExpiration(expiration);

                // 指定标签 test = 1，test 为标签名，1为标签值
                // 文档见 https://forums.aws.amazon.com/thread.jspa?threadID=252054&tstart=0

                // generatePresignedUrlRequest.putCustomRequestHeader(Headers.S3_TAGGING, "test=1");
                // 生成 presigned URL，用该 URL 可以进行该对象的上传
                //

                URL url = conn.generatePresignedUrl(generatePresignedUrlRequest);
                System.out.println("Pre-Signed URL: " + url.toString());

                OkHttpClient ok_http = new OkHttpClient();
                File file = new File("download_file");
                RequestBody formBody = new MultipartBody.Builder()
                                           .setType(MultipartBody.FORM)
                                           .addFormDataPart("file", file.getName(),
                                                            RequestBody.create(MediaType.parse("text/plain"), file))
                                           .addFormDataPart("other_field", "other_field_value")
                                           .build();
                Request request = new Request.Builder().url(url.toString()).put(formBody).build();
                Response response = ok_http.newCall(request).execute();
                System.out.println(" --- " + response.message());

                // HttpURLConnection connection = (HttpURLConnection) url.openConnection();
                // connection.setDoOutput(true);
                // connection.setRequestMethod("PUT");
                // OutputStreamWriter out = new OutputStreamWriter(connection.getOutputStream());
                // out.write("This text uploaded as an object via presigned URL.");
                // out.close();

                // 检查 HTTP 响应码
                // connection.getResponseCode();
                // System.out.println("HTTP response code: " + connection.getResponseCode());

                // 确认对象上传成功
                S3Object object = conn.getObject("test-new", "哦");
                System.out.println("Object " + object.getKey() + " created in bucket " + object.getBucketName());
            }


        } catch(AmazonServiceException e) {
            e.printStackTrace();
        } catch(SdkClientException e) {
            e.printStackTrace();
        } catch(IOException e) {
            e.printStackTrace();
        }
    }

    public static void listBucket(String bucketName)
    {
        ObjectListing list = conn.listObjects(bucketName);
        List<S3ObjectSummary> los = list.getObjectSummaries();
        for (S3ObjectSummary obj: los) {
            System.out.println(obj.getKey());
        }
    }


    public static void main( String[] args )
    {
        System.out.println( "Hello World!" );

        try {
              // conn.createBucket(bucketName);

              // conn.createBucket("test-new");

              // ObjectMetadata md = new ObjectMetadata();
              // md.setContentLength(0);
              // conn.putObject("test-new", "enming/", new ByteArrayInputStream(new byte[0]), md);

              listBucket("em777");
//            conn.putObject(bucketName, "dir2", new ByteArrayInputStream(new byte[0]), md);
//
              // conn.putObject(bucketName, "presigned-put-test", "TEST");
//
//            ByteArrayInputStream input = new ByteArrayInputStream("Hello World!".getBytes());
//            conn.putObject(bucketName, "big_file", input, new ObjectMetadata());
//
//            PutObjectRequest request = new PutObjectRequest(bucketName, sourceKey, new File(sourceKey));
//            ObjectMetadata metadata = new ObjectMetadata();
//            metadata.setContentType("plain/text");
//            metadata.addUserMetadata("x-amz-meta-title", "someTitle");
//            request.setMetadata(metadata);
//            conn.putObject(request);
//
//            multiPartUpload(bucketName, "big_file", "big_file");
//
//            CopyObjectRequest copyObjRequest = new CopyObjectRequest(bucketName, "big_file", bucketName, destinationKey);
//            conn.copyObject(copyObjRequest);
//
            // usePresignedURLPutObject();


            // // listBucket(bucketName);
            // listBucket("test-new");

            System.out.println( "Everything seems ok" );
        } catch(AmazonServiceException e) {
            // The call was transmitted successfully, but Amazon S3 couldn't process
            // it, so it returned an error response.
            e.printStackTrace();
        } catch(SdkClientException e) {
            // Amazon S3 couldn't be contacted for a response, or the client
            // couldn't parse the response from Amazon S3.
            e.printStackTrace();
        }

    }
}
