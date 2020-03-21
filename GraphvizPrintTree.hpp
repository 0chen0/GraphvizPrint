//参考: https://blog.nanpuyue.com/2019/054.html
/*
.\build\xxx.exe && dot -Tpng .\print_tree.gv -o print_tree.png
*/
#ifndef CZH_GraphvizPrintTree_HPP
#define CZH_GraphvizPrintTree_HPP
#include <fstream>
#include <string>

namespace CZH
{
namespace GraphvizPrintTree
{

template<typename T>
class TreePrintNode
{
public:
    virtual TreePrintNode* left()=0;
    virtual TreePrintNode* right()=0;
    virtual const std::string color(){ return std::string("black"); }
    virtual T& val()=0;
};

template<typename T>
class PrintTree
{
	TreePrintNode<T>* root_;
	std::ofstream output_;
public:
	PrintTree(TreePrintNode<T>* root, const char* filename):root_(root),output_(filename){}
	~PrintTree(){ output_.close(); }
	void printSelf()
	{		
		if(auto x = root_){
			output_ << "digraph G {" << std::endl;
			output_ << "	graph [nodesep=0.1]" << std::endl;
			output_ << "	node [shape=circle]" << std::endl;
			output_ << "	edge [arrowhead=vee]" << std::endl;
			if(x->left() || x->right()){				
				output_ << "	" << x->val() << " [group=" << x->val() << " color=" << x->color() << "]" << std::endl;
			}
			printNode(x);
			output_ << "}" << std::endl;
		}
	}
private:
	void printNode(TreePrintNode<T>* node)
	{
		T* target = nullptr;
		int distance = 0;
		if(auto x1 = node->left()){
			auto left_max = x1;
			int left_distance = 1;
			while(auto x2 = left_max->right()){
				left_max = x2;
				left_distance += 1;
			}
			target = &left_max->val();
			distance = left_distance;

			// if(x1->left || x1->right){
				output_ << "	" << x1->val() << " [group=" << x1->val() << " color=" << x1->color() << "]" << std::endl;
			// }
			output_ << "	" << node->val() << " -> " << x1->val() << std::endl;
			printNode(x1);			
		}

		if(node->left() || node->right()){
			output_ << "	_" << node->val() 
				<< " [group=" << node->val() << ", label=\"\", width=0, style=invis]" << std::endl;
			output_ << "	" << node->val() << " -> _" << node->val() << " [style=invis]" << std::endl;
		}

		if(auto x1 = node->right()){
			auto right_min = x1;
			int right_distance = 1;
			while(auto x2 = right_min->left()){
				right_min = x2;
				right_distance += 1;				
			}
			if (right_distance <= distance){
				target = &right_min->val();
				distance = right_distance;
			}

			// if(x1->left || x1->right){
				output_ << "	" << x1->val() << " [group=" << x1->val() << " color=" << x1->color() << "]" << std::endl;
			// }
			output_ << "	" << node->val() << " -> " << x1->val() << std::endl;
			printNode(x1);
		}

		if(distance > 1){
			if(auto x = target){
				output_ << "	{rank=same; _" << node->val() << "; " << *x << "}" << std::endl;
			}
		}
	}

};

} // namespace GraphvizPrintTree
} // namespace CZH
#endif // CZH_GraphvizPrintTree_HPP