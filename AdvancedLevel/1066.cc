#include <bits/stdc++.h>
using namespace std;
struct node {
    int elem, height;
    node *l, *r;
};
inline void UpdateHeight( node *root ) { root->height = max( root->l ? root->l->height : 0, root->r ? root->r->height : 0 ) + 1; }
inline int GetBlcIndex( node *root ) { return ( root->l ? root->l->height : 0 ) - ( root->r ? root->r->height : 0 ); }
node *RR( node *root ) {
    node *right = root->r;
    root->r = right->l;
    right->l = root;
    UpdateHeight( root );  // Update the original node
    return right;
}
node *LL( node *root ) {
    node *left = root->l;
    root->l = left->r;
    left->r = root;
    UpdateHeight( root );  // Update the original node, and if the new root node is not the real root of the tree then the real root will be updated in the first level insertion.
    return left;
}
node *RL( node *root ) {
    root->r = LL( root->r );
    return RR( root );
}
node *LR( node *root ) {
    root->l = RR( root->l );
    return LL( root );
}
node *insert( node *root, int _elem, function<bool( int, int )> const &leftIs = less<>{} ) {
    if ( root == nullptr ) {
        return new node{ _elem, 1, nullptr, nullptr };  // ~~Aggerate Initialization~~List Initilization Since C++ 17
    } else if ( leftIs( _elem, root->elem ) ) {
        root->l = insert( root->l, _elem, leftIs );
        if ( GetBlcIndex( root ) == 2 ) {               // left is higher
            root = GetBlcIndex( root->l ) > 0 ? LL( root ) : LR( root );
        }
    } else {
        root->r = insert( root->r, _elem, leftIs );
        if ( GetBlcIndex( root ) == -2 ) {              // Right is higher
            root = GetBlcIndex( root->r ) < 0 ? RR( root ) : RL( root );
        }
    }
    UpdateHeight( root );                               // pure Update is only for GetBlcIndex, but root's height is not required before GetBlcIndex
                                                        // only required before GetBlcIndex, so put it in the return stack
    return root;
}
int main() {
    int nodeCnt;
    node *root = nullptr;
    cin >> nodeCnt;
    for ( int val, i = 0; i < nodeCnt && cin >> val; i++ ) {
        root = insert( root, val );
    }
    root ? ( cout << root->elem ) : ( cout << "" );
}
// And because of that getblcindex needs no root's height, the tree's root' height is not updated in LL or RR.
// The root's height is updated in the end of first node's insertion.