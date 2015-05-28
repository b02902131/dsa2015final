#include <utility>
#include <list>
using namespace std;
struct EmptyHeap: public std::exception {};

class E{
	public:
	int priority, id;
	bool operator < (const E& x)
	{
		return priority < x.priority;
	}
	bool operator <= (const E& x)
        {
                return priority <= x.priority;
        }
	bool operator > (const E& x)
        {
                return priority > x.priority;
        }
	bool operator >= (const E& x)
        {
                return priority >= x.priority;
        }
	bool operator == (const E& x)
        {
                return priority == x.priority;
        }
	bool operator != (const E& x)
        {
                return priority != x.priority;
        }
};
template<class T>
class BinomialHeap 
{
	private:
	/* inner class: binomial tree */
	struct BinomialTree 
	{
		int _size;
		T element;
		std::list<BinomialTree*> children;
		BinomialTree(T _ele): _size(1), element(_ele) 
		{
			children.clear();
		}
		int size() 
		{
			return (this != nullptr) ? this -> _size : 0;
		}
        };
	typedef BinomialTree BT;
	typedef BinomialHeap<T> BH;
	typedef std::pair<BT*, BT*> CarrySum;
	typedef std::pair<T, BH> MaxRemainder;

	CarrySum merge_tree(BT *a, BT *b, BT *c) 
	{
		CarrySum temp;
		if(a != nullptr && b != nullptr && c != nullptr)//need to deal with carry and current digit is 1
		{
			if(a -> element >= b -> element)
			{
				a -> _size += b -> _size;
				temp.first = a;
				temp.first -> children.push_back(b);
			}
			else
			{
				b -> _size += a -> _size;
				temp.first = b;
				temp.first -> children.push_back(a);
			}
			temp.second = c;
		}
		else if(a != nullptr && b != nullptr && c == nullptr)//need to deal with carry and current digit is 0
		{
			if(a -> element >= b -> element){
				a -> _size += b -> _size;
				temp.first = a;
				temp.first -> children.push_back(b);
			}
			else
			{
				b -> _size += a -> _size;
				temp.first = b;
				temp.first -> children.push_back(a);
			}
			temp.second = nullptr;
		}
		else if(a == nullptr && b != nullptr && c != nullptr)
		{
			if(b -> element >= c -> element)
			{
				b -> _size += c -> _size;
				temp.first = b;
				temp.first -> children.push_back(c);
			}
			else
			{
				c -> _size += b -> _size;
				temp.first = c;
				temp.first -> children.push_back(b);
			}
			temp.second = nullptr;
		}
		else if(a != nullptr && b == nullptr && c != nullptr)
                {
			if(a -> element >= c -> element){
				a -> _size += c -> _size;
				temp.first = a;
				temp.first -> children.push_back(c);
			}
			else
			{
				c -> _size += a -> _size;
				temp.first = c;
				temp.first -> children.push_back(a);
			}
			temp.second = nullptr;
		}
		else if(a != nullptr && b == nullptr && c == nullptr)//not need to deal with carry and current digit is 1
		{
			temp.first = nullptr;
			temp.second = a;
		}
		else if(a == nullptr && b != nullptr && c == nullptr)//not need to deal with carry and current digit is 1
		{
			temp.first = nullptr;
			temp.second = b;
		}
		else if(a == nullptr && b == nullptr && c != nullptr)//not need to deal with carry and current digit is 1
		{
			temp.first = nullptr;
			temp.second = c;
		}
		else if(a == nullptr && b == nullptr && c == nullptr)//not need to deal with carry and current digit is 0
		{
			temp.first = nullptr;
			temp.second = nullptr;
		}	
		return temp;	
	}
	int calculateIndex(int x)
	{
		int count = 0;
		while(x != 0)
		{
			x /= 2;
			++count;
		}
		return count - 1;
	}
	MaxRemainder pop_max(BT *a) 
	{
		MaxRemainder temp;
		temp.first = a -> element;
		for(typename list<BinomialTree*>::iterator it = a -> children.begin(); it != a -> children.end(); it++)
			temp.second.trees[calculateIndex((*it) -> size())] = *it;
		delete a;
		return temp;
	}
	int size;
	BT* trees[32]; //binomial trees of the binomial heap, where trees[i] is a tree with size 2^i.

	public:
	BinomialHeap(): size(0) 
	{
		for(int i = 0; i < 32; ++i) trees[i] = nullptr;
        }
        BinomialHeap(T element): size(1) 
	{
		for(int i = 0; i < 32; ++i) trees[i] = nullptr;
		trees[0] = new BT(element);
	}
	void merge(BH &b) 
	{
		CarrySum temp = merge_tree(trees[0], b.trees[0], nullptr);//trees[0] must not have carry
		trees[0] = temp.second;
		b.trees[0] = nullptr;
		for(int i = 1; i < 32; i++)
		{
			temp = merge_tree(trees[i], b.trees[i], temp.first);
			b.trees[i] = nullptr;
			trees[i] = temp.second;
		}
		size += b.size;
		b.size = 0;
	}
        void insert(const T &element) 
	{
		BH tmp = BH(element);
		merge(tmp);
	}
	int Size()
	{
		return size;
	}
	int findMax()
	{
		int max = -1;
		for(int i = 0; i < 32; i++)
			if(trees[i] != nullptr && trees[i] -> size() > 0 && (max == -1 || trees[i] -> element.priority > max))
				max = trees[i] -> element.priority;
		return max;
	}
	T pop() 
	{
		if(size == 0) throw EmptyHeap();
		else    //find the tree contains maximum element
		{
			int max_tree = -1;
			for(int i = 0; i < 32; i++)
				if(trees[i] != nullptr && trees[i] -> size() > 0 && (max_tree == -1 || trees[i] -> element > trees[max_tree] -> element))
						max_tree = i;
			MaxRemainder m_r = pop_max(trees[max_tree]);
			T &max_element = m_r.first;
			BH &remainder = m_r.second;
			trees[max_tree] = nullptr;
			merge(remainder);
			--size;
			return max_element;
		}
	}
};
