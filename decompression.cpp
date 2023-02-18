#include "decompression.h"

// Binary node 
struct BinaryNode{
      char data;
      BinaryNode *left,*right,*parent;

      BinaryNode(char data){
          left=right=parent=NULL;
          this->data=data;
     }
};

// Insert every element to the binary tree
void insert (BinaryNode* root, char data, string code){
    //If root is Null then return.
    if(!root){
        return;
    }
    // Base case
    if(code == "0"){
        BinaryNode* node = new BinaryNode(data);
        root->left = node;
        node->parent = root;
    }
    else if(code == "1"){
        BinaryNode* node = new BinaryNode(data);
        root->right = node;
        node->parent = root;
    }


    if(code[0] == '0' && code.size() != 1){
        if(!root->left){
            BinaryNode* node = new BinaryNode(code[0]);
            root->left = node;
            node->parent = root;
        }
        insert(root->left, data, code.substr(1));
    }
    else if(code[0] == '1' && code.size() != 1){
        if(!root->right){
            BinaryNode* node = new BinaryNode(code[0]);
            root->right = node;
            node->parent = root;
        }
        insert(root->right, data, code.substr(1));
    }
}

// Get the data as a binary tree
BinaryNode* getBinaryTree(string s){
    BinaryNode* root = new BinaryNode('$');
    int i = 0;
    int size = s.size();
    while(i != size-1){
        if(s[i] == ','){
            char data = s[i+1];
            i+=2;
            string code;
            while(s[i] != ','){
                string c (1,s[i]);
                code.append(""+c);
                i++;
            }
            insert(root, data, code);
        }
    }
    return root;
}

// For Testing
void treeTraversal(BinaryNode* root){
    //If root is Null then return.
    if(!root){
        return;
    }

    // Base case
    if(!root->left && !root->right){
        cout << root->data << endl;
    }

    if(root->left){
        treeTraversal(root->left);
    }
    if(root->right){
        treeTraversal(root->right);
    }
}

// get the data by traversing the encoded data into the binary tree 
void getData(BinaryNode* root, string code, string& s){
    //If root is Null then return.
    if(!root){
        return;
    }

    BinaryNode* current = root;
    while(code.size() != 0){

        if(code[0] == '0' && current->left){
            current = current->left;
            code = code.substr(1);
        }else if(code[0] == '1' && current->right){
            current = current->right;
            code = code.substr(1);
        }

        // Base case
        if(!current->left && !current->right){
            s.append(1,current->data);
            current = root;
        }
    }
}

// Convert the file from encoded to binary
string toBinary(string encoded){
    string out;
    int condition = encoded[encoded.size()-1]-48;
    int a = encoded.size();
    for(int i = 0; i < encoded.size()-1; i++){
        if(i < encoded.size()-condition-1){
            encoded[i] = encoded[i] - 30;
            std::bitset<7> b(encoded[i]);
            out.append(b.to_string());
        }else{
            string s(1,encoded[i]);
            out.append(s);
        }
    }
    return out;
}

// Decompress Function
void decompress(string compressed){
    // Open file
    ifstream infile;
    infile.open(compressed);

    string dataCodes;
    string encodedData;

    if(infile.is_open()){
        // Get the data codes
        getline(infile,dataCodes);
        
        // Get the encoded data
        getline(infile, encodedData);

        infile.close();
    }
    else{
        cout << "Err" << endl;
    }

    // convert it to binary
    encodedData = toBinary(encodedData);
    
    // Put the data codes in the tree 
    BinaryNode* BinaryTree = getBinaryTree(dataCodes);

    //treeTraversal(BinaryTree);
    // Decode the data
    string data;
    getData(BinaryTree, encodedData, data);
    
    // Finally, put the xml to the decompressed file 
    ofstream ofile;
    ofile.open("decompressed/decompressed");
    ofile << data;
    ofile.close();
}


int main(){
    // To decompress
    decompress("compressed/compressed.huf");

    /*_____________________________________Decompress Testing_____________________________________*/
    
    /*____________________________________Get gile Testing____________________________________*/
    /*ifstream infile;
    infile.open("compressed.huf");

    string dataCodes;
    string encodedData;

    if(infile.is_open()){
        // Get the data codes
        getline(infile,dataCodes);
        
        // Get the encoded data
        getline(infile, encodedData);

        infile.close();
    }
    else{
        cout << "Err" << endl;
    }

    //cout<< dataCodes << endl;
    //cout << encodedData << endl;

    //BinaryNode* BinaryTree = getBinaryTree(dataCodes);
    //treeTraversal(BinaryTree);

    // convert it to binary
    encodedData = toBinary(encodedData);
    toEmpty(encodedData);
    cout << "encoded data : " << encodedData << endl;
    /*ofstream binaryFile;
    binaryFile.open("binary_decompressed.txt");
    binaryFile<<encodedData;
    binaryFile.close();*/
    
    system("pause");
    return 0;
}


