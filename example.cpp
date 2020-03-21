#include "GraphvizPrintTree.hpp"

using namespace CZH::GraphvizPrintTree;

class TreeNode : public TreePrintNode<int>
{
public:
	int val_;
	std::string color_;
	TreeNode* left_;
	TreeNode* right_;
	TreeNode(int value, const char* clr):val_(value), color_(clr), left_(nullptr), right_(nullptr){}
	TreeNode(int value, const char* clr, TreeNode* &parent):val_(value), color_(clr), left_(nullptr), right_(nullptr)
	{
		parent = this;
	}
	const std::string color(){ return color_; }
	TreeNode* left() { return left_; }
	TreeNode* right() { return right_; }
	int& val() { return val_; }
};

void main()
{
	TreeNode n30(30, "black");	
		TreeNode n15(15, "black", n30.left_);
			TreeNode n10(10, "black", n15.left_);
				TreeNode n5(5, "red", n10.left_);
			TreeNode n20(20, "black", n15.right_);
				// TreeNode n25(25, "red", n20.right_);
				TreeNode n18(18, "red", n20.left_);
		TreeNode n70(70, "black", n30.right_);		
			TreeNode n60(60, "red", n70.left_);
				TreeNode n50(50, "black", n60.left_);
					TreeNode n40(40, "red", n50.left_);
					TreeNode n55(55, "red", n50.right_);
				TreeNode n65(65, "black", n60.right_);
					TreeNode n63(63, "red", n65.left_);
					TreeNode n68(68, "red", n65.right_);
			TreeNode n85(85, "black", n70.right_);
				TreeNode n80(80, "red", n85.left_);
				TreeNode n90(90, "red", n85.right_);

	
	PrintTree<int> s(&n30, "print_tree.gv");
	s.printSelf();

}