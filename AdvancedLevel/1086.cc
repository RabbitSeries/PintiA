#include <bits/stdc++.h>
struct bst {
    using tree = std::shared_ptr<bst>;
    int data;
    tree l, r;
    bst( int _data ) : data{ _data } {}
};
std::vector<int> output;
void postorder( bst::tree root ) {
    if ( !root ) {
        return;
    }
    postorder( root->l );
    postorder( root->r );
    output.push_back( root->data );
}
int main() {
    int nodeN;
    std::stack<bst::tree> st;
    bst::tree current, root;
    std::cin >> nodeN;
    getchar();  // EOL
    for ( std::string op; int _ : std::views::iota( 0, nodeN * 2 ) ) {
        std::getline( std::cin, op );
        if ( op.starts_with( "Push" ) ) {
            int data = std::stoi( op.substr( 5 ) );
            auto node = std::make_shared<bst>( data );
            if ( !root ) {
                root = node;
            } else {
                if ( current->l ) {
                    current->r = node;
                } else {
                    current->l = node;
                }
            }
            st.push( node );
            current = st.top();
        } else {
            current = st.top();
            st.pop();
        }
    }
    postorder( root );
    for ( int i = 0; i < nodeN; i++ ) {
        std::cout << ( i ? " " : "" ) << output[i];
    }
}
