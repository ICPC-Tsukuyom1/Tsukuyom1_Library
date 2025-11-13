#include <bits/extc++.h>

using namespace __gnu_pbds;

template <class T>
using Tree =
    tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

template <class T>
using MultiTree = tree<T, null_type, less_equal<T>, rb_tree_tag,
                       tree_order_statistics_node_update>;

template <class... Args>
using FastMap = gp_hash_table<Args...>;
