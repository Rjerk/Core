radosgw-admin user create --uid=javasdk-test --display-name="javasdk-test" --access-key="javasdk-test" --secret-key="javasdk-test"

s3cmd mb s3://src

s3cmd mb s3://des

s3cmd put pom.xml s3://src
