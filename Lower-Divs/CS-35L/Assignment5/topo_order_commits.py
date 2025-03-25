#!/usr/bin/env python3

# Recommended libraries. Not all of them may be needed.
import copy, os, sys, re, zlib
from collections import deque

# Note: This is the class for a doubly linked list. Some implementations of
# this assignment only require the `self.parents` field. Delete the
# `self.children` field if you don't think its necessary.
class CommitNode:
    def __init__(self, commit_hash):
        """
        :type commit_hash: str
        """
        self.commit_hash = commit_hash
        self.parents = set()
        self.children = set()


# ============================================================================
# ======================== Auxiliary Functions ===============================
# ============================================================================

def in_git_directory() -> bool:
    """
    :rtype: bool

    Checks if `topo_order_commits.py` is inside a Git repository.
    """
    while os.getcwd() != "/" and '.git' not in os.listdir():
        os.chdir('..')
    return '.git' in os.listdir()

def recursive_walk(curr_path, rel_path, branches):
    references = os.listdir(curr_path)

    # go through all files
    for ref in references:
        path = os.path.join(curr_path, ref)
        curr_branch = rel_path + ref
        
        # check for subdirectories
        if os.path.isdir(path):
            recursive_walk(path, curr_branch + '/', branches)
        # save to branches if file
        elif os.path.isfile(path):
            with open(path, 'r') as f:
                commit_hash = f.read().strip()
                branches.append((curr_branch, commit_hash))

def get_parents(commit_hash):
    parents = []
    git_path = get_git_directory()
    parent_path = os.path.join(git_path, 'objects', commit_hash[:2], commit_hash[2:])
    if os.path.exists(parent_path):
        decompressed_data = decompress_git_object(parent_path)
        # check for parent in file contents
        for i in range(len(decompressed_data)):
            if decompressed_data[i] == "parent":
                parents.append(decompressed_data[i + 1])
    return parents


def decompress_git_object(commit_path : str) -> list[str]:
    """
    :type commit_hash: str
    :rtype: list

    Decompresses the contents of a git object and returns a
    list of the decompressed contents.
    """
    with open(commit_path, 'rb') as file:
        compressed_data = file.read()
        decompressed_data = zlib.decompress(compressed_data)

    return decompressed_data.decode().split()


# ============================================================================
# =================== Part 1: Discover the .git directory ====================
# ============================================================================

def get_git_directory() -> str:
    """
    :rtype: str
    Returns absolute path of `.git` directory.
    """
    # check if .git exists
    if not in_git_directory():
        sys.stderr.write("Not inside a Git repository\n")
        exit(1)

    # get absolute path
    git_path = os.path.join(os.getcwd(), '.git')

    # ensure this is a directory
    if not os.path.isdir(git_path):
        sys.stderr.write("Not inside a Git repository\n")
        exit(1)

    return git_path

    

# ============================================================================ 
# =================== Part 2: Get the list of local branch names =============
# ============================================================================

def get_branches(path : str) -> list[(str, str)]:
    """
    :type path: str
    :rtype: list[(str, str)]

    Returns a list of tupes of branch names and the commit hash
    of the head of the branch.
    """
    branches = []
    directory_path = os.path.join(path, 'refs', 'heads')
    recursive_walk(directory_path, '', branches)
    return branches




# ============================================================================
# =================== Part 3: Build the commit graph =========================
# ============================================================================

def build_commit_graph(branches_list : list[(str, str)]) -> dict[str, CommitNode]:
    """
    :type branches_list: list[(str, str)]
    :rtype: dict[str, CommitNode]

    Iterative builds the commit graph from the list of branches and
    returns a dictionary mapping commit hashes to commit nodes.
    """
    graph = {}
    seen = set()

    branch_hashes = []
    for branch in branches_list:
        branch_hashes.append(branch[1])
    
    while branch_hashes:
        curr = branch_hashes.pop()
        if curr in seen:
            continue
        else:
            seen.add(curr)
            if curr not in graph:
                graph[curr] = CommitNode(curr)
            
            parents = get_parents(curr)
            curr_node = graph[curr]
            for p_hash in parents:
                if p_hash not in seen:
                    branch_hashes.append(p_hash)
                if p_hash not in graph:
                    graph[p_hash] = CommitNode(p_hash)
                graph[p_hash].children.add(curr)
                curr_node.parents.add(p_hash)

    return graph
            
          


# ============================================================================
# ========= Part 4: Generate a topological ordering of the commits ===========
# ============================================================================

def topo_sort(root_commits: list[CommitNode]) -> list[str]:
    """
    :type root_commits: list[CommitNode]
    :rtype: list[str]

    Generates a topological ordering of the commits in the commit graph.
    The topological ordering is represented as a list of commit hashes. See
    the LA Worksheet for some starter code for Khan's algorithm.
    """
    sorted_list = []
    commits_copy = copy.deepcopy(root_commits)
    no_children = []

    # populate set for commits with no incoming edges (children)
    for commit in commits_copy:
        if not commits_copy[commit].children:
            no_children.append(commits_copy[commit])

    while (bool(no_children)):
        curr_node = no_children.pop()
        sorted_list.append(curr_node) 
        # check current commits ancestors
        for parent in list(curr_node.parents):
            p_node = commits_copy[parent]
            p_node.children.remove(curr_node.commit_hash)

            if not any(p_node.children):
                no_children.append(p_node)
        
    # Cycle detected
    if len(sorted_list) < len(root_commits):
        sys.exit(1)
    else:
        return sorted_list


# ============================================================================
# ===================== Part 5: Print the commit hashes ======================
# ============================================================================

def ordered_print(
    commit_nodes : dict[str, CommitNode],
    topo_ordered_commits : list[str],
    head_to_branches : dict[str, list[str]]
):
    """
    :type commit_nodes: dict[str, CommitNode]
    :type topo_ordered_commits: list[str]
    :type head_to_branches: dict[str, list[str]]

    Prints the commit hashes in the the topological order from the last
    step. Also, handles sticky ends and printing the corresponding branch
    names with each commit.
    """
    sticky = False

    # go through every commit
    for i in range(len(topo_ordered_commits)):
        print_msg = topo_ordered_commits[i].commit_hash

        # print current commit hash followed by the branches
        for branch in head_to_branches:
            branch_name, branch_hash = branch[0], branch[1]
            if branch_hash == topo_ordered_commits[i].commit_hash:
                print_msg += ' ' + branch_name

        # if the next commit isn't a parent of the current commit
        if i + 1 < len(topo_ordered_commits):
            next_commit = topo_ordered_commits[i + 1]
            if next_commit.commit_hash not in topo_ordered_commits[i].parents:
                print_msg += '\n'
                first_child = True
                # sort for deterministic
                sorted_parents = sorted(topo_ordered_commits[i].parents)
                for parent in sorted_parents:
                    if first_child:
                        print_msg += parent
                        first_child = False
                    else:
                        print_msg += ' ' + parent
                print_msg += '=' + '\n'
                sticky = True

        print(print_msg)
            
        if sticky:
            sticky = False
            next_commit = topo_ordered_commits[i + 1]
            sticky_end = '='
            first_child = True
            # sort to make deterministic
            sorted_children = sorted(commit_nodes[next_commit.commit_hash].children)
            
            for child in sorted_children:
                if first_child:
                    first_child = False
                    sticky_end += child
                else:
                    sticky_end += ' ' + child

            print(sticky_end)


# ============================================================================
# ==================== Topologically Order Commits ===========================
# ============================================================================

def topo_order_commits():
    """
    Combines everything together.
    """
    
    # Check if you are inside a Git repository.
    
    # Part 1: Discover the .git directory.
    git_path = get_git_directory()
    
    # Part 2: Get the list of local branch names.
    branches = get_branches(git_path)

    # Part 3: Build the commit graph

    # Generate a list of root `CommitNode`s
    commit_graph = build_commit_graph(branches)

    # Part 4: Generate a topological ordering of the commits in the graph.

    # Generate the head_to_branches dictionary showing which
    # branches correspond to each head commit
    topo_sorted = topo_sort(commit_graph)

    # Part 5: Print the commit hashes in the topological order.
    ordered_print(commit_graph, topo_sorted, branches)

    

# ============================================================================

if __name__ == '__main__':
    topo_order_commits()

