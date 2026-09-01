#include <stdint.h>
#include <stdlib.h>

typedef struct CmlOrderedNode {
  int64_t key;
  int64_t count;
  int height;
  struct CmlOrderedNode *left;
  struct CmlOrderedNode *right;
} CmlOrderedNode;

typedef struct {
  CmlOrderedNode *root;
  int64_t size;
} CmlOrdered;

static int height(const CmlOrderedNode *node) { return node == NULL ? 0 : node->height; }

static int maximum(int left, int right) { return left > right ? left : right; }

static void update(CmlOrderedNode *node) {
  node->height = 1 + maximum(height(node->left), height(node->right));
}

static CmlOrderedNode *rotate_left(CmlOrderedNode *node) {
  CmlOrderedNode *root = node->right;
  node->right = root->left;
  root->left = node;
  update(node);
  update(root);
  return root;
}

static CmlOrderedNode *rotate_right(CmlOrderedNode *node) {
  CmlOrderedNode *root = node->left;
  node->left = root->right;
  root->right = node;
  update(node);
  update(root);
  return root;
}

static CmlOrderedNode *balance(CmlOrderedNode *node) {
  if (node == NULL)
    return NULL;
  update(node);
  int factor = height(node->left) - height(node->right);
  if (factor > 1) {
    if (height(node->left->left) < height(node->left->right))
      node->left = rotate_left(node->left);
    return rotate_right(node);
  }
  if (factor < -1) {
    if (height(node->right->right) < height(node->right->left))
      node->right = rotate_right(node->right);
    return rotate_left(node);
  }
  return node;
}

static CmlOrderedNode *create_node(int64_t key) {
  CmlOrderedNode *node = (CmlOrderedNode *)malloc(sizeof(CmlOrderedNode));
  if (node == NULL)
    abort();
  node->key = key;
  node->count = 1;
  node->height = 1;
  node->left = NULL;
  node->right = NULL;
  return node;
}

static CmlOrderedNode *insert(CmlOrderedNode *node, int64_t key) {
  if (node == NULL)
    return create_node(key);
  if (key < node->key)
    node->left = insert(node->left, key);
  else if (key > node->key)
    node->right = insert(node->right, key);
  else {
    ++node->count;
    return node;
  }
  return balance(node);
}

static CmlOrderedNode *first_node(CmlOrderedNode *node) {
  while (node->left != NULL)
    node = node->left;
  return node;
}

static CmlOrderedNode *erase(CmlOrderedNode *node, int64_t key, int *removed) {
  if (node == NULL)
    return NULL;
  if (key < node->key) {
    node->left = erase(node->left, key, removed);
  } else if (key > node->key) {
    node->right = erase(node->right, key, removed);
  } else {
    *removed = 1;
    if (node->count > 1) {
      --node->count;
      return node;
    }
    if (node->left == NULL || node->right == NULL) {
      CmlOrderedNode *child = node->left != NULL ? node->left : node->right;
      free(node);
      return child;
    }
    CmlOrderedNode *successor = first_node(node->right);
    node->key = successor->key;
    node->count = successor->count;
    successor->count = 1;
    int ignored = 0;
    node->right = erase(node->right, successor->key, &ignored);
  }
  return balance(node);
}

void *toy_ordered_create(int64_t capacity_hint) {
  (void)capacity_hint;
  CmlOrdered *set = (CmlOrdered *)calloc(1, sizeof(CmlOrdered));
  if (set == NULL)
    abort();
  return set;
}

void toy_ordered_insert(void *handle, int64_t key) {
  CmlOrdered *set = (CmlOrdered *)handle;
  set->root = insert(set->root, key);
  ++set->size;
}

void toy_ordered_erase(void *handle, int64_t key) {
  CmlOrdered *set = (CmlOrdered *)handle;
  int removed = 0;
  set->root = erase(set->root, key, &removed);
  set->size -= removed;
}

static int64_t ceiling(const CmlOrdered *set, int64_t key, int64_t fallback) {
  CmlOrderedNode *node = set->root;
  int64_t result = fallback;
  while (node != NULL) {
    if (node->key >= key) {
      result = node->key;
      node = node->left;
    } else {
      node = node->right;
    }
  }
  return result;
}

static int64_t higher(const CmlOrdered *set, int64_t key, int64_t fallback) {
  CmlOrderedNode *node = set->root;
  int64_t result = fallback;
  while (node != NULL) {
    if (node->key > key) {
      result = node->key;
      node = node->left;
    } else {
      node = node->right;
    }
  }
  return result;
}

static int64_t floor_key(const CmlOrdered *set, int64_t key, int64_t fallback) {
  CmlOrderedNode *node = set->root;
  int64_t result = fallback;
  while (node != NULL) {
    if (node->key <= key) {
      result = node->key;
      node = node->right;
    } else {
      node = node->left;
    }
  }
  return result;
}

int64_t toy_ordered_query(const void *handle, int64_t key, int64_t mode,
                          int64_t default_value) {
  const CmlOrdered *set = (const CmlOrdered *)handle;
  if (mode == 0)
    return ceiling(set, key, default_value);
  if (mode == 1)
    return higher(set, key, default_value);
  if (mode == 2)
    return floor_key(set, key, default_value);
  if (mode == 3)
    return set->root == NULL ? default_value : first_node(set->root)->key;
  if (mode == 4) {
    CmlOrderedNode *node = set->root;
    if (node == NULL)
      return default_value;
    while (node->right != NULL)
      node = node->right;
    return node->key;
  }
  return set->size;
}