#include <iostream>
#include <algorithm>
#include <list>
#include <vector>
#include <stack>
#include <initializer_list>
#include <string>
#include <cstdlib>
#include <ctime>
#include <random>

class Node {  // This class represents each node in the behaviour tree.
	public:
		std::string name;
		int probabilityOfSuccess;
		virtual bool run() = 0;
};

class Action : public Node {
	public:
		std::string name;
		int probabilityOfSuccess;
		Action (const std::string newName, int prob) : name(newName), probabilityOfSuccess(prob) {}
	private:
		virtual bool run() override {
			if (std::rand() % 100 < probabilityOfSuccess) {
				std::cout << name << " succeeded." << std::endl;
				return true;
			}
			std::cout << name << " failed." << std::endl;
			return false;
		}
};

class BehaviourTree {  // Note:  A proper copy constructor and assignment operator should be defined, since the implicit ones use shallow copies only.
	public:
		class CompositeNode : public Node {  //  This type of Node follows the Composite Pattern, containing a list of other Nodes.
			private:
				std::vector<Node*> children;
			public:
				const std::vector<Node*>& getChildren() const {return children;}
				void addChild (Node* child) {children.emplace_back(child);}
				void addChildren (std::initializer_list<Node*>&& newChildren) {for (Node* child : newChildren) addChild(child);}
				template <typename CONTAINER>
				void addChildren (const CONTAINER& newChildren) {for (Node* child : newChildren) addChild(child);}
			protected:
				std::vector<Node*> childrenShuffled() const 
				{
					std::vector<Node*> temp = children;
					std::random_device rd;
					std::mt19937 g(rd());  
					std::shuffle(temp.begin(), temp.end(), g);  
					return temp;
				}
		};
		
		class Selector : public CompositeNode {
			public:
				virtual bool run() override {
					for (Node* child : getChildren()) {  // The generic Selector implementation
						if (child->run())  // If one child succeeds, the entire operation run() succeeds.  Failure only results if all children fail.
						{	
							// Node* dummy = child;
							// Action *pChild =  (Action *) &dummy;
							// std::cout << "TEST" << pChild->name << "TEST\n";
							return true;
						}
					}
					return false;  // All children failed so the entire run() operation fails.
				}
		};
		
		class RandomSelector : public CompositeNode {  // RandomSelector operates as a Selector, but in a random order instead of from first child to last child.
			public:
				virtual bool run() override {
					for (Node* child : childrenShuffled()) {  // The order is shuffled
						if (child->run())
							return true;
					}
					return false;
				}
		};

		class Sequence : public CompositeNode {
			public:
				virtual bool run() override {
					for (Node* child : getChildren()) {  // The generic Sequence implementation.
						if (!child->run())  // If one child fails, then enter operation run() fails.  Success only results if all children succeed.
							return false;
					}
					return true;  // All children suceeded, so the entire run() operation succeeds.
				}
		};

		class Root : public Node {
			private:
				Node* child;
				friend class BehaviourTree;
				void setChild (Node* newChild) {child = newChild;}
				virtual bool run() override {return child->run();}
		};
	private:
		Root* root;
	public:
		BehaviourTree() : root(new Root) {}
		void setRootChild (Node* rootChild) const {root->setChild (rootChild);}
		bool run() const {return root->run();}
};

int main() {
	std::srand(std::time(nullptr));
	BehaviourTree behaviorTree;
	BehaviourTree::Selector selector[3];
	BehaviourTree::Sequence sequence[4];
	Action walkToDoor ("Walk to door", 99), openDoor1 ("Open door", 15), unlockDoor ("Unlock door", 25), openDoor2 ("Open door after unlocking it", 99), smashDoor ("Smash door", 60), 
		walkThroughDoor ("Walk through door", 60), closeDoor ("Close door", 100), walkToWindow ("Walk to Window", 99), openWindow1 ("Open window", 70), unlockWindow ("Unlock window", 65),
		openWindow2 ("Open window after unlocking it", 85), smashWindow ("Smash window", 95), climbThroughWindow ("Climb through window", 85), closeWindow ("Close window", 100);
	
	behaviorTree.setRootChild (&selector[0]);
	selector[0].addChildren ({&sequence[0],&sequence[2]});
	sequence[0].addChildren ({&walkToDoor, &selector[1], &walkThroughDoor, &closeDoor});
	selector[1].addChildren ({&openDoor1, &sequence[1], &smashDoor});
	sequence[1].addChildren ({&unlockDoor, &openDoor2});
	sequence[2].addChildren ({&walkToWindow, &selector[2], &climbThroughWindow, &closeWindow});
	const std::list<Node*> nodes = {&openWindow1, &sequence[3], &smashWindow};
	selector[2].addChildren(nodes);
	sequence[3].addChildren ({&unlockWindow, &openWindow2});
	
	if (behaviorTree.run())
		std::cout << "Congratulations!  You made it out!" << std::endl;
	else
		std::cout << "Sorry.  You are trapped here for life." << std::endl;
}