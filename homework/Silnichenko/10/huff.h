#ifndef HUFF_H__
#define HUFF_H__
#include <iostream>
#include <string>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
class MyException
{
	private:
	const std::string cause_;
	public:
	MyException();
	MyException(const char *cause);
	~MyException();
	void Handle();
};
MyException::MyException(): cause_("nothing")
{
}
MyException::MyException(const char *cause): cause_(cause)
{
}
MyException::~MyException()
{
}
void MyException::Handle()
{
	std::cout << cause_ << std::endl;
}
/*my exception class above*/
namespace Const
{
	const uint64_t buflen=256;
	const uint32_t bytesize=8;
}
class HuffTreeNode
{
	friend class HuffTree;
	friend uint32_t RCode(const char *fin, const char *fout);
	private:
	uint64_t weight_;
	uint8_t value_;
	bool leaf_;
	HuffTreeNode *left_;
	HuffTreeNode *right_;
	public:
	HuffTreeNode();
	~HuffTreeNode();
	HuffTreeNode(uint64_t w, uint8_t v, bool l);
	HuffTreeNode(const HuffTreeNode &n);
	HuffTreeNode operator=(const HuffTreeNode &n);
};
HuffTreeNode::HuffTreeNode(): weight_(0), value_(0), leaf_(false), left_(nullptr), right_(nullptr)
{
}
HuffTreeNode::~HuffTreeNode()
{
	//delete left_;
	//delete right_;
}
HuffTreeNode::HuffTreeNode(uint64_t w, uint8_t v, bool l): weight_(w), value_(v), leaf_(l), left_(nullptr), right_(nullptr)
{
}
HuffTreeNode::HuffTreeNode(const HuffTreeNode &n): weight_(n.weight_), value_(n.value_), leaf_(n.leaf_), left_(n.left_), right_(n.right_)
{
}
HuffTreeNode HuffTreeNode::operator=(const HuffTreeNode &n)
{
	weight_=n.weight_;
	value_=n.value_;
	leaf_=n.leaf_;
	left_=n.left_;
	right_=n.right_;
	return *this;
}
class BitSet
{
	friend class HuffTree;
	friend std::ostream& operator<<(std::ostream &out, const BitSet &a);
	private:
	uint8_t *bytes_;
	uint32_t size_;
	public:
	BitSet();
	~BitSet();
	BitSet(uint32_t s);
	BitSet(const uint8_t *u, uint32_t s);
	BitSet(const BitSet &b);
	BitSet operator=(const BitSet &b);
	void Set(uint32_t offset, bool value);
	bool Get(uint32_t offset) const;
	const uint8_t * gBytes();
	
};
BitSet::BitSet(): bytes_(nullptr), size_(0)
{
}
BitSet::~BitSet()
{
	delete[] bytes_;
}
BitSet::BitSet(uint32_t s): size_(s)
{
	uint32_t r=(s%Const::bytesize==0)? 0 : 1;
	uint32_t result_size=s/Const::bytesize+r;
	bytes_=new uint8_t[result_size];
}
BitSet::BitSet(const uint8_t *u, uint32_t s): size_(s)
{
	uint32_t r=(s%Const::bytesize==0)? 0 : 1;
	uint32_t result_size=s/Const::bytesize+r;
	bytes_=new uint8_t[result_size];
	for(uint32_t i=0; i<result_size; i++)
	{
		bytes_[i]=u[i];
	}
}
BitSet::BitSet(const BitSet &b): size_(b.size_)
{
	uint32_t r=(size_%Const::bytesize==0)? 0 : 1;
	uint32_t result_size=size_/Const::bytesize+r;
	bytes_=new uint8_t[result_size];
	std::copy(b.bytes_, b.bytes_+result_size, bytes_);
}
BitSet BitSet::operator=(const BitSet &b)
{
	delete[] bytes_;
	size_=b.size_;
	uint32_t r=(size_%Const::bytesize==0)? 0 : 1;
	uint32_t result_size=size_/Const::bytesize+r;
	bytes_=new uint8_t[result_size];
	std::copy(b.bytes_, b.bytes_+result_size, bytes_);
	return *this;
}
void BitSet::Set(uint32_t offset, bool value)
{
	if(offset>=size_)
	{
		throw MyException("this bit is not in set");
	}
	const uint8_t h=1<<(Const::bytesize-offset%Const::bytesize-1);
	uint8_t v=(value)? h : ~h; //change offsets
	bytes_[offset/Const::bytesize]=(value)? bytes_[offset/Const::bytesize]|v : bytes_[offset/Const::bytesize]&v;
}
bool BitSet::Get(uint32_t offset) const
{
	if(offset>=size_)
	{
		throw MyException("this bit is not in set");
	}
	return (bytes_[offset/Const::bytesize]>>(Const::bytesize-offset%Const::bytesize-1))%2==1;
}
const uint8_t * BitSet::gBytes()
{
	return bytes_;
}
std::ostream& operator<<(std::ostream &out, const BitSet &a);
std::ostream& operator<<(std::ostream &out, const BitSet &a)
{
	for (uint32_t i=0; i<a.size_; i++)
	{
		if(a.Get(i))
		{
			out << '1';
		}
		else
		{
			out << '0';
		}
	}
	return out;
}
class AHuffTree
{
	/*Huffman-Adaptive*/
	
};
class HuffTree
{
	/*Huffman-nonAdaptive*/
	friend uint32_t RCode(const char *fin, const char *fout);
	private:
	HuffTreeNode root_;
	BitSet *codes_;
	HuffTreeNode *nodes_;
	void Encode();
	void EncodeWalk(const HuffTreeNode *n, BitSet code, int8_t s);
	public:
	HuffTree();
	~HuffTree();
	HuffTree(const uint64_t *weights, const uint8_t *vals);
	uint32_t WCode(const char *fin, const char *fout, const uint64_t *weights) const;
	//const HuffTreeNode * gRoot();
	//const BitSet* gCodes();
};
HuffTree::HuffTree(): root_(), codes_(nullptr), nodes_(nullptr)
{
}
HuffTree::~HuffTree()
{
	delete[] codes_;
	delete[] nodes_;
}
void HuffTree::EncodeWalk(const HuffTreeNode *n, BitSet code, int8_t s)
{
	if(n->leaf_)
	{
		code.size_=s;
		codes_[n->value_]=code;
		//std::cout << code << " " << n->value_ << " " << (int32_t)s << std::endl;
	}
	else
	{
		code.Set(s, false);
		EncodeWalk(n->left_, code, s+1);
		code.Set(s, true);
		EncodeWalk(n->right_, code, s+1);
	}
}
void HuffTree::Encode()
{
	//std::cout << "Encodin'\n";
	BitSet b(Const::buflen);
	b.Set(0, false);
	EncodeWalk(root_.left_, b, 1);
	b.Set(0, true);
	EncodeWalk(root_.right_, b, 1);
}
HuffTree::HuffTree(const uint64_t *weights, const uint8_t *vals)
{
	/*weights array is sorted*/
	HuffTreeNode tmp;
	uint32_t i=0;
	uint8_t j=0;
	uint8_t k=0; //counts nonleaf nodes
	nodes_=new HuffTreeNode[2*Const::buflen];
	//std::cout << "Tree construction started\n";
	for(i=0; i<Const::buflen; i++)
	{
		nodes_[i]=HuffTreeNode(weights[i], vals[i], true);
	}
	//std::cout << "Leaves finished\n";
	/*now we'll add new nodes*/
	nodes_[Const::buflen]=HuffTreeNode(weights[0]+weights[1], 0, false);
	nodes_[Const::buflen].left_=nodes_;
	nodes_[Const::buflen].right_=nodes_+1;
	k=1;
	i=2;
	while(k<Const::buflen-1)
	{
		if(i<Const::buflen)
		{
			if((!(j<k)) || nodes_[i].weight_<=nodes_[j+Const::buflen].weight_)
			{
				if(i<Const::buflen-1 && nodes_[i+1].weight_<=nodes_[j+Const::buflen].weight_)
				{/*unite two leaves*/
					nodes_[Const::buflen+k]=HuffTreeNode(weights[i]+weights[i+1], 0, false);
					nodes_[Const::buflen+k].left_=nodes_+i;
					nodes_[Const::buflen+k].right_=nodes_+i+1;
					i+=2;
				}
				else
				{/*leaf and non-leaf*/
					nodes_[Const::buflen+k]=HuffTreeNode(weights[i]+nodes_[j+Const::buflen].weight_, 0, false);
					nodes_[Const::buflen+k].left_=nodes_+i;
					nodes_[Const::buflen+k].right_=nodes_+Const::buflen+j;
					i++;
					j++;
				}
			}
			else
			{/*leaves are heavier than first non-leaf*/
				if(j<k-1 && nodes_[j+Const::buflen+1].weight_<=nodes_[i].weight_)
				{/*two non-leaves*/
					nodes_[Const::buflen+k]=HuffTreeNode(nodes_[j+Const::buflen].weight_+nodes_[j+Const::buflen+1].weight_, 0, false);
					nodes_[Const::buflen+k].left_=nodes_+Const::buflen+j;
					nodes_[Const::buflen+k].right_=nodes_+Const::buflen+j+1;
					j+=2;
				}
				else
				{/*leaf and non-leaf*/
					nodes_[Const::buflen+k]=HuffTreeNode(weights[i]+nodes_[j+Const::buflen].weight_, 0, false);
					nodes_[Const::buflen+k].left_=nodes_+Const::buflen+j;
					nodes_[Const::buflen+k].right_=nodes_+i;
					i++;
					j++;
				}
			}
		}
		else
		{/*only non-leaves remain*/
			nodes_[Const::buflen+k]=HuffTreeNode(nodes_[j+Const::buflen].weight_+nodes_[j+Const::buflen+1].weight_, 0, false);
			nodes_[Const::buflen+k].left_=nodes_+Const::buflen+j;
			nodes_[Const::buflen+k].right_=nodes_+Const::buflen+j+1;
			j+=2;
		}
		k++;
		//std::cout << k << std::endl;
	}
	root_=nodes_[2*Const::buflen-2];
	codes_=new BitSet[Const::buflen];
	/*find out codes for values*/
	Encode();
}
uint32_t HuffTree::WCode(const char *fin, const char *fout, const uint64_t *weights) const
{
	uint8_t ibuf[Const::buflen];
	uint32_t count=0;
	uint32_t wcount;
	uint32_t wsum=0, k=0;
	FILE *in, *out;
	BitSet obuf(Const::buflen*Const::bytesize);
	in=fopen(fin, "rb");
	if(in==NULL)
	{
		throw(MyException("can't open file"));
	}
	out=fopen(fout, "wb");
	fwrite(weights, sizeof(uint64_t), Const::buflen, out); //table written
	while(!feof(in))
	{
		uint32_t tmp=fread(ibuf, sizeof(uint8_t), Const::buflen, in);
		for(uint32_t i=0; i<tmp; i++)
		{
			uint32_t csz=codes_[ibuf[i]].size_;
			for(uint32_t j=0; j<csz; j++)
			{
				obuf.Set(k, codes_[ibuf[i]].Get(j)); //was codes[i]
				k++;
				if(k==Const::buflen*Const::bytesize)
				{
					wcount=fwrite(obuf.bytes_, sizeof(uint8_t), Const::buflen, out);
					if(wcount!=Const::buflen)
					{
						throw MyException("writing error");
					}
					k=0;
					wsum+=wcount;
				}
			}
		}
	}
	int32_t rem=(k%Const::bytesize==0)? k/Const::bytesize : k/Const::bytesize+1;
	wcount=fwrite(obuf.bytes_, sizeof(uint8_t), rem, out);
	if(rem!=wcount)
	{
		throw MyException("writing error");
	}
	wsum+=wcount;
	fclose(in);
	fclose(out);
	return wsum;
}
/*const HuffTreeNode *HuffTree::gRoot()
{
	return &root_;
}*/
/*huffman-tree above*/
int32_t TableGen(const char *fname, uint64_t *w);
//int32_t WCode(const char *fin, const char *fout, HuffTree code); //&
uint32_t RCode(const char *fin, const char *fout);
typedef struct
{
	uint64_t w;
	uint8_t v;
} Wbyte;
int32_t Cmp(const void *a, const void *b);
int32_t Cmp(const void *a, const void *b)
{
	Wbyte *na=(Wbyte *)a;
	Wbyte *nb=(Wbyte *)b;
	if(na->w>nb->w)
	{
		return 1;
	}
	if(na->w<nb->w)
	{
		return -1;
	}
	return 0;
}
/*non-class functions*/
int32_t TableGen(const char *fname, uint64_t *w)
{
	FILE *in;
	uint32_t i, tmp;
	uint8_t buf[Const::buflen];
	in=fopen(fname, "rb");
	if(in==NULL)
	{
		return -1;
	}
	for(i=0; i<Const::buflen; i++)
	{
		w[i]=0;
	}
	while(!feof(in))
	{
		tmp=fread(buf, sizeof(uint8_t), Const::buflen, in);
		for(i=0; i<tmp; i++)
		{
			w[buf[i]]++;
		}
	}
	fclose(in);
	return 0;
}
uint32_t RCode(const char *fin, const char *fout)
{
	FILE *in, *out;
	uint64_t w[Const::buflen];
	uint8_t v[Const::buflen];
	uint8_t buf[Const::buflen];
	uint8_t obuf[Const::buflen];
	uint32_t ocount=0, oc=0;
	uint64_t checksum=0;
	Wbyte *tab;
	in=fopen(fin, "rb");
	fread(w, sizeof(uint64_t), Const::buflen, in);
	tab=new Wbyte[Const::buflen];
	for(uint32_t i=0; i<Const::buflen; i++)
	{
		tab[i].w=w[i];
		tab[i].v=i;
		checksum+=w[i];
		//std::cout << i << " " << w[i] << std::endl;
	}
	qsort(tab, Const::buflen, sizeof(Wbyte), Cmp);
	for(uint32_t i=0; i<Const::buflen; i++)
	{
		w[i]=tab[i].w;
		v[i]=tab[i].v;
		//std::cout << i << " " << w[i] << " " << v[i] << std::endl;
	}
	HuffTree t(w, v);
	HuffTreeNode *h=&(t.root_);
	out=fopen(fout, "wb");
	while(!feof(in))
	{
		uint32_t tmp=fread(buf, sizeof(uint8_t), Const::buflen, in);
		BitSet bs(buf, tmp*Const::bytesize);
		for(uint32_t i=0; i<tmp*Const::bytesize; i++)
		{
			if(bs.Get(i))
			{
				h=h->right_;
			}
			else
			{
				h=h->left_;
			}
			if(h->leaf_)
			{
				//std::cout << h->value_ <<std::endl;
				obuf[oc]=h->value_;
				oc++;
				h=&(t.root_);
			}
			if(oc==Const::buflen)
			{
				fwrite(obuf, sizeof(uint8_t), oc, out);
				ocount+=oc;
				oc=0;
			}
		}
	}
	fwrite(obuf, sizeof(uint8_t), checksum-ocount, out);//test
	ocount+=oc;
	fclose(in);
	fclose(out);
	delete[] tab;
	return ocount;
}
#endif
