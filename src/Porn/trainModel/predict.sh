
## INPUT is a segment outcome
INPUT=$1

cd ../classify/textModel
## predict
for(( i = 1; i <=20; i++ ))
do
	modelname="model."$i".gram"
	outname=$INPUT".out."$i
	logname="x."$i".gram"
	./src/main.gram $INPUT tmp/$modelname > log/$logname
	mv $INPUT".out" out/$outname
	pornout="pornScore."$i
	cat out/$outname| awk "/��˿|����|�԰�|ɫ��|ȫ��|����|�Ը߳�|�ٸ�|AV|av|˿��|�㽻|�Խ�|��Ů|��ɧ|����|����|����|����|����|���|������|ëƬ|����|���|�д�|��Ƭ|�ڱ�/" > tmp/$pornout
done

## vote the output
python vote.py out
cat $INPUT".ter" | sort -t "	" -k 2 -n > $INPUT".ter.sort"
