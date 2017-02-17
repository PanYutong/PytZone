class Solution {

  public:

    bool isValidBST(TreeNode* root) {
      if (root) return true;
      bool ret = true;
      if (root->left->val < root->val) isValidBST(root->left)?ret = true:return false;
      else return false;
      if (root->right->val > root->val) isValidBST(root->right)?ret = true:return false;
      else return false;
      return ret;
    }

};
