#ifndef EPHYLO_H
#define EPHYLO_H

#include <R.h>
#include <Rinternals.h>

/*
** If another R package wants to make use of these APIs it 
** simply needs to add the ephylo package as an entry in the 
** Depends and LinkingTo targets in its Description file. It 
** can then #include this file in its own sources. Be sure to
** #define EPHYLO_API_IMPLEMENTATION before #include'ing (and
** only in one place if there will be more than one #include).
** Be aware that all the nodes in the tree structure are
** indexed beginning from 1 because they are coming from R
** and will need to be decremented by 1 for use in C.
*/

typedef struct tree {
    int num_tips;
    int num_nodes;
    int root;
    const int *parent;
    const int *left_child;
    const int *right_child;
    const int *left_sib;
    const int *right_sib;
    const int *left_sample;
    const int *right_sample;
    const int *next_sample;
    const double *time;
    const double *brlen;
    const int *preorder_nodes;
    const int *postorder_nodes;
} tree_t;


void ephylo_tree(tree_t *, SEXP);


#ifdef EPHYLO_API_IMPLEMENTATION

static const int *
EPHYLO_INTEGER_ELT(SEXP ephy, const char *str)
{
    int n = Rf_length(ephy);
    int *elmt = 0;
    SEXP names = PROTECT(Rf_getAttrib(ephy, R_NamesSymbol));
    for (int i = 0; i < n; i++)
    {
        if (strcmp(CHAR(STRING_ELT(names, i)), str) == 0)
        {
            elmt = INTEGER(VECTOR_ELT(ephy, i));
            break;
        }
    }
    UNPROTECT(1);
    return elmt;
}


static const double *
EPHYLO_REAL_ELT(SEXP ephy, const char *str)
{
    int n = Rf_length(ephy);
    double *elmt = 0;
    SEXP names = PROTECT(Rf_getAttrib(ephy, R_NamesSymbol));
    for (int i = 0; i < n; i++)
    {
        if (strcmp(CHAR(STRING_ELT(names, i)), str) == 0)
        {
            elmt = REAL(VECTOR_ELT(ephy, i));
            break;
        }
    }
    UNPROTECT(1);
    return elmt;
}


void
ephylo_tree(tree_t *tree, SEXP ephy)
{
    tree->num_tips = *(EPHYLO_INTEGER_ELT(ephy, "num.tips"));
    tree->num_nodes = *(EPHYLO_INTEGER_ELT(ephy, "num.nodes"));
    tree->root = tree->num_tips;
    tree->parent = EPHYLO_INTEGER_ELT(ephy, "parent");
    tree->left_child = EPHYLO_INTEGER_ELT(ephy, "left.child");
    tree->right_child = EPHYLO_INTEGER_ELT(ephy, "right.child");
    tree->left_sib = EPHYLO_INTEGER_ELT(ephy, "left.sib");
    tree->right_sib = EPHYLO_INTEGER_ELT(ephy, "right.sib");
    tree->left_sample = EPHYLO_INTEGER_ELT(ephy, "left.sample");
    tree->right_sample = EPHYLO_INTEGER_ELT(ephy, "right.sample");
    tree->next_sample = EPHYLO_INTEGER_ELT(ephy, "next.sample");
    tree->time = EPHYLO_REAL_ELT(ephy, "time");
    tree->brlen = EPHYLO_REAL_ELT(ephy, "brlen");
    tree->preorder_nodes = EPHYLO_INTEGER_ELT(ephy, "preorder.nodes");
    tree->postorder_nodes = EPHYLO_INTEGER_ELT(ephy, "postorder.nodes");
}

#endif

#endif
