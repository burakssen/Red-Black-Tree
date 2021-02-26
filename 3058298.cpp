// Name:  Burak Şen
// ID  :  150170063
// please use c++ 11 or higher compilers 
#include <iostream>

#include <fstream>
#include <string>

class Node
{
    std::string color;
    Node* left{};
    Node* right{};
    Node* parent{};
    std::string key;
    int point;
    int rebound;
    int assists;
public:
    Node(std::string, int, int, int);
    Node();
    void UpdateData(Node*);
    void operator=(Node*);
    bool operator==(Node*);
    bool operator!=(Node*);
    void setColor(std::string);
    void setLeft(Node*);
    void setRight(Node*);
    void setParent(Node*);
    std::string getColor();
    std::string getKey();
    Node* getLeft();
    Node* getRight();
    Node* getParent();
    int getPoint();
    int getRebound();
    int getAssits();

    ~Node();
};

class Red_Black_Tree {
    Node* root; // root node
    Node* NIL;  // nil node
    std::string season; // season
    std::string firstSeason;    // first season
    int printDeep = 0;  // tree level for indentation
    bool found = false;
    Node* maxPoints;    // max point player
    Node* maxAssists;   // max assist player
    Node* maxRebs;      // max rebs player

public:
    Red_Black_Tree();
    void Left_Rotate(Node*);
    void Right_Rotate(Node*);
    void Insert(Node*);
    void Insert_FixUp(Node*);
    void SetSeason(std::string);
    void UpdateNode(Node*,Node*);
    void SetPlayer(std::string, Node*);
    void printSeason(Node*);
    void deleteAllNodes(Node*);

    ~Red_Black_Tree();

};

void readFile(Red_Black_Tree *, const std::string&);

int main(int argc, char**argv) {
    std::string filename(argv[1]); // get filename from command line
    if(filename != "euroleague.csv")
    {
	std::cout<<"You did not enter the proper filename"<<std::endl;
	std::cout<<"You Entered: "<<filename<<std::endl;
	return 1;
    }

    Red_Black_Tree *rb_tree;   // create tree pointer
    rb_tree = new Red_Black_Tree(); // create new tree

    readFile(rb_tree, filename); // get all the data from file and insert the tree
    rb_tree->SetSeason("FINISH");
    delete rb_tree; // delete the tree
    return 0;
}

void readFile(Red_Black_Tree *myTree, const std::string& filename) {
    std::fstream file; // create file object

    file.open(filename);    // set filename

    std::string first_line; // this is header line

    std::getline(file, first_line, '\n');  //  get firstline (header line)

    std::string season, name, team, rebound, assist, point; // set variables
    Node* temp; // create temp node
    while (!file.eof()) {
        std::getline(file, season, ',');  // get lines
        std::getline(file, name, ',');
        std::getline(file, team, ',');
        std::getline(file, rebound, ',');
        std::getline(file, assist, ',');
        std::getline(file, point, '\n');
        temp = new Node(name, std::atoi(point.c_str()), std::atoi(rebound.c_str()), std::atoi(assist.c_str())); // create a new node (player)
        myTree->SetPlayer(season, temp); // set player with season
        delete temp;    // delete temp node
    }
}

Node::Node(std::string key, int point, int rebound, int assists) {  // node constructor sets variables
    this->left = nullptr;
    this->parent = nullptr;
    this->right = nullptr;
    this->key = key;
    this->point = point;
    this->rebound = rebound;
    this->assists = assists;
}

Node::Node(){   // default node constructor sets some values to 0
    this->point = 0;
    this->rebound = 0;
    this->assists = 0;
}

// operators

void Node::operator=(Node* data) {  // = operator assign's a node to another node
    this->left = data->left;
    this->parent = data->parent;
    this->right = data->right;
    this->key = data->key;
    this->point = data->point;
    this->rebound = data->rebound;
    this->assists = data->assists;
}

bool Node::operator==(Node *data) { // == operator controls if node's are same or not
    if(data->left == this->left &&
       data->parent == this->parent &&
       data->right == this->right &&
       data->key == this->key &&
       data->point == this->point &&
       data->rebound == this->rebound &&
       data->assists == this->assists){
        return true;
    }
    return false;
}

bool Node::operator!=(Node *data) { // !=  operator controls if node's are same or not
    if(data->left != this->left ||
       data->parent != this->parent ||
       data->right != this->right ||
       data->key != this->key ||
       data->point != this->point ||
       data->rebound != this->rebound ||
       data->assists != this->assists){
        return true;
    }
    return false;
}

void Node::UpdateData(Node*key) { // update data function updates scores
    this->point += key->point;
    this->rebound += key->rebound;
    this->assists += key->assists;
}

// setter functions

void Node::setColor(std::string color) {
    this->color = color;
}

void Node::setLeft(Node *left) {
    this->left = left;
}

void Node::setRight(Node *right) {
    this->right = right;
}

void Node::setParent(Node *parent) {
    this->parent = parent;
}

// getter functions

std::string Node::getColor() {
    return this->color;
}

std::string Node::getKey() {
    return this->key;
}

Node *Node::getLeft() {
    return this->left;
}

Node *Node::getRight() {
    return this->right;
}

Node *Node::getParent() {
    return this->parent;
}

int Node::getPoint() {
    return this->point;
}

int Node::getRebound() {
    return this->rebound;
}

int Node::getAssits() {
    return this->assists;
}

Node::~Node() {

}

Red_Black_Tree::Red_Black_Tree() {  // red_black tree constructor
    this->NIL = new Node("NIL",0,0,0);  // create nil node
    this->NIL->setColor("BLACK");   // set nil node black
    this->root = this->NIL; // because ther is no node in the root we placed nil as a root
    this->season = "";  // set season empty
    this->maxPoints = new Node();   // create blank max player nodes
    this->maxAssists = new Node();
    this->maxRebs = new Node();
}

void Red_Black_Tree::Left_Rotate(Node *parentNode) {    // rotate left method
    Node* child = parentNode->getRight();   // save parentNode's right
    parentNode->setRight(child->getLeft()); // set parentNode's right to parent node's right's left
    if(child->getLeft() != this->NIL){  // if child is not nil node
        child->getLeft()->setParent(parentNode);    // set child's left's parent as parent node
    }
    child->setParent(parentNode->getParent());  // set child's parent as parentNode's parent
    if(parentNode->getParent() == this->NIL){   //if parentNode's parent is nil node
        this->root = child; // the root is parentNode's right (which is child)
    }
    else if(parentNode == parentNode->getParent()->getLeft()){  // if parentNode is it's parents left child
        parentNode->getParent()->setLeft(child);    // set its parents left as child node
    }
    else{
        parentNode->getParent()->setRight(child);   // else set its parents right as child node
    }
    child->setLeft(parentNode); // set cihld's left as paretNode
    parentNode->setParent(child);   // and set parentNode's parent as child
}

void Red_Black_Tree::Right_Rotate(Node *parentNode) {   // rotate right
    Node* child = parentNode->getLeft();    // save parentNode's left
    parentNode->setLeft(child->getRight()); // set parentNode's left to parentNode's left's right
    if(child->getRight() != this->NIL){ // if child is not nil node
        child->getRight()->setParent(parentNode);   // set child's right's parent as parent node
    }
    child->setParent(parentNode->getParent()); // set child's parent as parentNode's parent
    if(parentNode->getParent() == this->NIL){   // if parentNode's parent is nil node
        this->root = child; // set root as parentNode's right (which is child)
    }
    else if(parentNode == parentNode->getParent()->getRight()){ // if parentNode is paretNode's parent's right child
        parentNode->getParent()->setRight(child);   // set parentNode's parent's right child to child node
    }
    else{
        parentNode->getParent()->setLeft(child);    // set parentNode's parent's left child to child node
    }
    child->setRight(parentNode);// set cihld's right as paretNode
    parentNode->setParent(child); // and set parentNode's parent as child
}

void Red_Black_Tree::Insert(Node* node){ // Node Insert function
    Node* newNode;  // new node pointer
    newNode = new Node();   // create new blank node
    *newNode = node;    // set new node properties

    Node* nilNode = this->NIL;  // get nil node
    Node* rootNode = this->root;    // get root node

    while(rootNode != this->NIL){   // if root node is not nil node (if there is a node in the root)
        nilNode = rootNode; // set nilnode to rootNode
        if(newNode->getKey().compare(rootNode->getKey()) < 0){  // if newNode's key is before rootNode
            rootNode = rootNode->getLeft(); // go to left of the root node
        }
        else{   // else
            rootNode = rootNode->getRight();    // go to right of the root node
        }
    }
    newNode->setParent(nilNode);    // set new nodes parent as nilNode which is now in the middle of somewhere if rootNode is not nil node
    if(nilNode == this->NIL){   // if nilNode is still NIL if (there is no node in the root node)
        this->root = newNode;   // set root as new Node
    }
    else if(newNode->getKey().compare(nilNode->getKey()) < 0){  //else check if newnode's key is before nilnode's key
        nilNode->setLeft(newNode);  // set nilnode's left as newnode
    }
    else{
        nilNode->setRight(newNode); //else set nilNode's right as newnode
    }

    newNode->setLeft(this->NIL);    // set newnode's right and left to this->NIL
    newNode->setRight(this->NIL);
    newNode->setColor("RED");   // set new node's color to RED
    this->Insert_FixUp(newNode); // when we set newnode's color to red some violations can happen because of that we call Insert_Fixup method with newnode
}

void Red_Black_Tree::Insert_FixUp(Node *node) {
    Node* uncle; // uncle node pointer
    while(node->getParent()->getColor() == "RED"){ // if node's parent is red
        if(node->getParent() == node->getParent()->getParent()->getLeft()){ // if node's parent is node's parent's parent's left child
            uncle = node->getParent()->getParent()->getRight(); // uncle is node's parent's parent's right child
            // 1. case
            if(uncle->getColor() == "RED"){ // if uncle's color is red
                node->getParent()->setColor("BLACK");    // change the node's parent color to black
                uncle->setColor("BLACK");   // change uncle's color to black
                node->getParent()->getParent()->setColor("RED");    // change node's parent's parent's color to red
                node = node->getParent()->getParent();  // and set node as node's parent's parent
            }// 2. case
            else if(node == node->getParent()->getRight()){ // else if node is it's parent's right child
                node = node->getParent();   // set node ar node's parent
                this->Left_Rotate(node);    // and left rotate
            }//3. case
            else{   // else
                node->getParent()->setColor("BLACK");   // set node's parent's color as black
                node->getParent()->getParent()->setColor("RED");    // set node's parent's parent's color to red
                this->Right_Rotate(node->getParent()->getParent()); // and right rotate node's parent's parent
            }
        }
        else{       // in here it's reverse
            uncle = node->getParent()->getParent()->getLeft();
            if(uncle->getColor() == "RED"){
                node->getParent()->setColor("BLACK");
                uncle->setColor("BLACK");
                node->getParent()->getParent()->setColor("RED");
                node = node->getParent()->getParent();
            }
            else if(node == node->getParent()->getLeft()){
                node = node->getParent();
                this->Right_Rotate(node);
            }
            else{
                node->getParent()->setColor("BLACK");
                node->getParent()->getParent()->setColor("RED");
                this->Left_Rotate(node->getParent()->getParent());
            }
        }
    }
    this->root->setColor("BLACK"); // and finally set root's color to black
}

void Red_Black_Tree::SetPlayer(std::string season, Node *player) { // in this function we choose update or insert player
    SetSeason(season);  // set current season

    if(this->season != season)          // if current season is not the same form argument
    {
        delete this->maxPoints;         // we delete this season's max point player
        this->maxPoints = new Node();   // create new black node
        delete this->maxRebs;           // we delete this season's max rebound player
        this->maxRebs = new Node();     // create new black node
        delete this->maxAssists;        // we delete this season's max assists player
        this->maxAssists = new Node();  // create new black node
    }



    if(this->firstSeason != season){ // if the season is not first season

        UpdateNode(this->root, player);  // update the player

        if(!this->found){ // if found is not true it is a new player
            this->Insert(player);   // add new player
        }
        this->found = false;
        return; // and return
    }

    if(player->getAssits() > this->maxAssists->getAssits()){    // if new player's assist is greater than max assist player node
        delete this->maxAssists; // delete the max assits player
        this->maxAssists = new Node(player->getKey(), player->getPoint(), player->getRebound(), player->getAssits()); // create new max assists node with new player
    }

    if(player->getRebound() >  this->maxRebs->getRebound()){// if new player's rebound is greater than max rebound player node
        delete this->maxRebs;// delete the max rebound player
        this->maxRebs = new Node(player->getKey(), player->getPoint(), player->getRebound(), player->getAssits());// create new max rebs node with new player
    }

    if(player->getPoint() > this->maxPoints->getPoint()){// if new player's point is greater than max point player node
        delete this->maxPoints;// delete the max point player
        this->maxPoints = new Node(player->getKey(), player->getPoint(), player->getRebound(), player->getAssits());// create new max point node with new player
    }

    this->Insert(player);   // if season is first season insert player
}

void Red_Black_Tree::SetSeason(std::string season) { // set season
    if(this->season != season){ // if season is not first season

        if(this->season != ""){ // and if season is not empty (when our season is not set yet)
            std::cout<<"End of the "<<this->season<<" Season"<<std::endl;   // print season
            std::cout<<"Max Points: "<<this->maxPoints->getPoint()<<" - Player Name: "<<this->maxPoints->getKey()<<std::endl;  // print max point player
            std::cout<<"Max Assists: "<<this->maxAssists->getAssits()<<" - Player Name: "<<this->maxAssists->getKey()<<std::endl;   // print max assists player
            std::cout<<"Max Rebs: "<<this->maxRebs->getRebound()<<" - Player Name: "<<this->maxRebs->getKey()<<std::endl;   // print max rebound player
        }
        else{
            this->firstSeason = season; // set first season if this season is empty
        }

        if(this->season == this->firstSeason){
            this->printSeason(this->root);// print the first seasons tree
        }

        this->season = season;  // set season
    }
}


void Red_Black_Tree::UpdateNode(Node *traverse, Node *key) { // update node
    // with this function we update a specific player
    if(traverse && !this->found){   // while there is a node in the traverse
        if(traverse->getKey() == key->getKey()){ // if our key node's key and traverse's key is equal we found the player
            this->found = true; // if player is in the list found is true
            traverse->UpdateData(key);  // update player information with key's information
            if(traverse->getAssits() > this->maxAssists->getAssits()){    // if updated player's assist is greater than max assist player node
                delete this->maxAssists; // delete the max assits player
                this->maxAssists = new Node(traverse->getKey(), traverse->getPoint(), traverse->getRebound(), traverse->getAssits()); // create new max assists node with new player
            }

            if(traverse->getRebound() >  this->maxRebs->getRebound()){// if updated player's rebound is greater than max rebound player node
                delete this->maxRebs;// delete the max rebound player
                this->maxRebs = new Node(traverse->getKey(), traverse->getPoint(), traverse->getRebound(), traverse->getAssits());// create new max rebs node with new player
            }

            if(traverse->getPoint() > this->maxPoints->getPoint()){// if updated player's point is greater than max point player node
                delete this->maxPoints;// delete the max point player
                this->maxPoints = new Node(traverse->getKey(), traverse->getPoint(), traverse->getRebound(), traverse->getAssits());// create new max point node with new player
            }
            // we don't have to change anything in the tree, tree is based on player's name we don't change the player's name
        }

        UpdateNode(traverse->getLeft(), key);   // go left in the tree
        UpdateNode(traverse->getRight(), key);  // go right in the tree
    }
}



void Red_Black_Tree::printSeason(Node*traverse) {   // print season function

    if(traverse->getKey() != "NIL"){ // if our key is not NIL we are in the tree
        for(int i = 0;i < printDeep; i++){  // we indent our player according to printDeep variable
            //print deep variable is increased when traverse goes on tree one level below and decreased when traverse goes on tree on level above
            std::cout<<"-";//print indentations
        }

        std::cout<<"("<<traverse->getColor()<<")"<<" "<<traverse->getKey()<<std::endl; // print color and player name
    }


    if(traverse->getLeft()){ // if there is a left node go to left node
        this->printDeep++;  // increase the printDeep variable when going below
        printSeason(traverse->getLeft());   // go left in tree
        this->printDeep--;  // decrease the printDeep variable when going above
    }

    if(traverse->getRight()){// if there is a right node go to right node
        this->printDeep++;// increase the printDeep variable when going below
        printSeason(traverse->getRight());// go right in tree
        this->printDeep--; // decrease the printDeep variable when going above
    }
}

void Red_Black_Tree::deleteAllNodes(Node* node) { // this function deletes all nodes
    if(node->getRight() != this->NIL){  // if our node is not nil node
        this->deleteAllNodes(node->getRight()); // go to right
    }

    if(node->getLeft() != this->NIL){   // if our node is not nil node
        this->deleteAllNodes(node->getLeft());  // go to left
    }
    // because there is only one nil node we can delete when our traverse reach each leafs we have to delete it ones
    delete node;    // delete nodes
}
Red_Black_Tree::~Red_Black_Tree() { // destructor
    deleteAllNodes(this->root); // delete all nodes other then the nil node
    delete this->maxAssists;    // delete max assists node
    delete this->maxPoints;     // delete max points node
    delete this->maxRebs;       // delete max rebs node
    delete this->NIL;           // delete nil node
}


