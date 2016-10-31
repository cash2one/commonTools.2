#include "AhoCorasick.h"
// iNumber �� ���ٸ���
// pLen[] 	��ÿ���ʵĳ���
// pattern[] : �ʵ�
int AhoCorasick::initialize(int iNumber, const int pLen[], const char* patterns[]) {
	for (int i = 0; i != iNumber; ++i) {  //�����ڵ�
		insert(patterns[i], pLen[i], i);	// ���� Trie ��
	}
	fixAhoCorasick();  //��дfailָ��
	return 0;
}

int AhoCorasick::release(trieNode* &p) {
	for (std::map<unsigned, trieNode*>::iterator it = p->next.begin(); it != p->next.end(); ++it) {
		release(it->second);
	}
	delete p;
	p = NULL;
	return 0;
}

int AhoCorasick::insert(const char* pattern, int pLen, int patternIndex) {
	if (pLen <= 0) return -1;  //�մ���Ҫ
	trieNode* p = root;	// ��ʼ��root�����Ϊparent ���
	for (int i = 0; i != pLen; ++i) { //ѭ������ײ�
		unsigned index = (unsigned char)pattern[i];	// �ʵ�ÿ��Ԫ��
		if (p->next.find(index) == p->next.end()) {	// ��ǰԪ�ز���parent��child���
			p->next[index] = new trieNode();		// Ϊ��ǰԪ������һ���µ� trieNode, �����뵽parent��child ��ϣ�б��
													// ��Ϊ������ÿһ���¼���Ĵʣ�����޷���root��child���ҵ����ߵ�path������ҪΪ������½���һ��child��path��
		}
		p = p->next[index];	// ����child path����ָ��p ָ���������Ϊ�µ�parent��㣬Ȼ��ѭ������ʣ�µĴʡ���root ���Ĳ���ͬ��
	}
	p->end = true;
	p->pIndex = patternIndex;
	return 0;
}

int AhoCorasick::fixAhoCorasick() {
	std::queue<trieNode*> nodeQueue;
	nodeQueue.push(root);
	while (nodeQueue.size() > 0) {
		trieNode* parent = nodeQueue.front();	// ��ȡ parent ���
		nodeQueue.pop();						// ��parent ����queue ɾ��

		// �����parent ��������child 
		// ���������һ����������ȱ���
		for (std::map<unsigned, trieNode*>::iterator it = parent->next.begin(); it != parent->next.end(); ++it) {
			unsigned index = it->first;		// child = index 
			trieNode* child = it->second;	// ����ҪΪ child �� trieNode �ṹ��ֵ
			if (parent == root) {
				child->fail = root;
			} else {
				trieNode* failp = parent->fail;// ����ȡ��parent ����ʧ����ָ
				while (failp != NULL) {		   // parent ����ʧ����ָ����
					if (failp->next.find(index) != failp->next.end()) {// parent ���ʧ����ָ�Ľ���child ����ڵ�ǰchild.
						child->fail = failp->next[index];	// ��ǰchild ��ʧ����ָ��parentʧ����ָ�����child��
						break;
					}
					failp = failp->fail;	// ��֮�����parent��ʧ����ָ����child ��û�е�ǰchild��������ݹ����parent��ʧ����ָ��ʧ����ָ����ҡ�ֱ���ݹ鵽���һ��ʧ����ָ��parent��
				}
				if (failp == NULL) child->fail = root;	// parent����ʧ����ָ�����ڣ���Ѹ�child��ʧ����ָ��Ϊ��root��㡣������������һ��child��
			}
			nodeQueue.push(child);		// ��child����Ϣѹ��queue����Ϊ�µ�parent��
		}  //for
	}  //while
}

/*
 *ƥ���Ӵ�
 *���룺������str������sLen
 *�����ģ�鴮�±꼰����str�е�λ�ã���ĩλ����ɵ�vector
 */
int AhoCorasick::search(const char* str, int sLen, std::vector<std::pair<unsigned, int> >& result) {
	result.clear();
	trieNode* p = root;
	for (int i = 0; i != sLen; ++i) {
		unsigned index = (unsigned char)str[i];	// ��ǰԪ�� index
		if (p == root && p->next.find(index) == p->next.end() ) // ���ڵ㺢�����Ҳ�����ǰԪ��index, ����������������һ��index��ʼ���ҡ�
			continue;

		while (p->next.find(index) == p->next.end() && p != root) {	// ��ǰԪ�ز���parent��child����parent ��Ϊroot������parent����ָ�����Ƿ��н����
			p = p->fail;
		}

		if (p == NULL || p->next.find(index) == p->next.end()) {	// �����ǰparent�������е���ָparent��û��index ���child
			p = root;
			continue;
		} else {	// ��ǰԪ����parent ��child����
			trieNode* q = p->fail;	// �ҵ�parent����ָ
			p = p->next[index];		// parent ���е���child
		}
		trieNode *q = p;	//	��child
		while (q) {
			if (q->end) {	// ��child ��trie����Ҷ�ӽ��,������ѹ��result ����С�
				result.push_back(std::make_pair(q->pIndex, i + 1));
			}
			q = q->fail;	// �ҵ���child����ָ������������û�п��Ը����Ľ����
		}
	}
	return 0;
}


