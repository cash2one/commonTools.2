testfile=$1
cat $testfile | /search/yonghuahu/tools/wordSegment/src/segment_bin > $testfile".seg"
testseg=$testfile".seg"

cd /search/yonghuahu/dm_/classify/textmodel
## predict
for(( i = 1; i <=20; i++ ))
do
	modelname="model."$i".gram"
	outname="test.dat.seg.out."$i
	logname="x."$i".gram"
	./src/main.gram $testseg $modelname > $logname
	mv $testseg".out" tmp/$outname
	pornout="pornScore."$i
	cat tmp/$outname| awk "/��˿|����|�԰�|ɫ��|ȫ��|����|�Ը߳�|�ٸ�|AV|av|˿��|�㽻|�Խ�|��Ů|��ɧ|����|����|����|����|����|���|������|ëƬ|����|���|�д�|��Ƭ|�ڱ�/" > tmp/$pornout
done

## vote the output
#python vote.py > test.dat.seg.out.ter

