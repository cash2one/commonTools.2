#! /usr/bin/python 
#encoding:gb18030
############################################
#
# Author: lichao
# Create time: 2014 11�� 30 00ʱ03��26��
# E-Mail: lichaotx020@sogou-inc.com
# version 1.0
#
############################################

import sys,os,re
from optparse import OptionParser
import gl

rex=re.compile(r'(^[a-zA-Z0-9]+$)')
for line in sys.stdin:
	line = line.strip()
	arr = line.split("\t")
	line = ""
	# ȥ������
	if len(arr[0]) < 3:
		continue

	# ȥ��������չ��
	for w in arr:
		loc = w.find(":")
		if loc > -1:
			ext = w[:loc]
			if len(ext) > 2:
				line = line + w + "\t"
			else:
				v = 1
		else:
			line = line + w + "\t"


	query = gl.strQ2B(arr[0].decode("gb18030")).encode("gb18030")
	# ��ĸ������
	if query.isalpha():
		sys.stdout.write("%s\n" % line)
		continue
	# ȥ�����ֺ���ĸ���
	if rex.match(query):
		continue;
	else:
		sys.stdout.write("%s\n" % line)

