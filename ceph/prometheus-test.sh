../src/stop.sh

make vstart

../src/vstart.sh -n -d --mon_num 1 --osd_num 3 --mds_num 0 --rgw_num 0

./bin/ceph mgr module ls

./bin/ceph mgr module enable prometheus

curl localhost:9283/metrics

./bin/rados mkpool test

for i in {1..100}
do
    ./bin/rados put $i Makefile --pool=test
    ./bin/ceph osd map test $i
done


for file in `ls dev/osd1/current/1.1_head/* dev/osd1/current/1.2_head/* dev/osd1/current/1.3_head/* dev/osd1/current/1.4_head/*`
do
    echo $file
    echo "1" > $file
done

./bin/ceph osd scrub osd.0
./bin/ceph osd scrub osd.1
./bin/ceph osd scrub osd.2


