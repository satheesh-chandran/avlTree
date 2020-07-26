const generateRandomArray = function (count) {
  const numbers = [];
  while (numbers.length != count) {
    const num = Math.ceil(Math.random() * 100);
    if (!numbers.includes(num)) numbers.push(num);
  }
  return numbers;
};

const createDivision = function (style) {
  const division = document.createElement('div');
  division.classList.add(style);
  return division;
};

const visualize = function (tree, parentElement) {
  if (tree == null) return;
  const divisions = ['text', 'side', 'side'].map(createDivision);
  divisions.forEach(div => parentElement.appendChild(div));
  divisions[0].innerText = tree.value;
  visualize(tree.left, divisions[1]);
  visualize(tree.right, divisions[2]);
};

const getHeight = node => (node ? node.height : 0);

const getBalanceFactor = node =>
  node ? getHeight(node.left) - getHeight(node.right) : 0;

const createNode = value => ({ value, left: null, right: null, height: 1 });

const updateHeight = function (node) {
  node.height = Math.max(getHeight(node.left), getHeight(node.right)) + 1;
};

const rightRotate = function (tree) {
  const temp = tree.left;
  tree.left = temp.right;
  temp.right = tree;
  updateHeight(tree);
  updateHeight(temp);
  return temp;
};

const leftRotate = function (tree) {
  const temp = tree.right;
  tree.right = temp.left;
  temp.left = tree;
  updateHeight(tree);
  updateHeight(temp);
  return temp;
};

const rotate = function (tree, value) {
  tree.height = 1 + Math.max(getHeight(tree.left), getHeight(tree.right));
  const heightRange = getBalanceFactor(tree);
  if (heightRange > 1 && value < tree.left.value) return rightRotate(tree);
  if (heightRange < -1 && value > tree.right.value) return leftRotate(tree);
  if (heightRange > 1 && value > tree.left.value) {
    tree.left = leftRotate(tree.left);
    return rightRotate(tree);
  }
  if (heightRange < -1 && value < tree.right.value) {
    tree.right = rightRotate(tree.right);
    return leftRotate(tree);
  }
  return tree;
};

const insert = function (tree, value) {
  if (tree == null) return createNode(value);
  if (value < tree.value) tree.left = insert(tree.left, value);
  else tree.right = insert(tree.right, value);
  return rotate(tree, value);
};

const isBalanced = function (tree) {
  if (tree == null) return true;
  const leftDepth = getHeight(tree.left);
  const rightDepth = getHeight(tree.right);
  const absoluteRange = Math.abs(leftDepth - rightDepth);
  return absoluteRange <= 1 && isBalanced(tree.left) && isBalanced(tree.right);
};

const deleteNode = function (tree, value) {
  if (tree == null) return tree;
  if (value < tree.value) tree.left = deleteNode(tree.left, value);
  if (value > tree.value) tree.right = deleteNode(tree.right, value);
};

const main = function () {
  // const list = [82, 1, 72, 50, 14, 99, 97, 37, 53, 80, 19, 98, 23];
  const list = generateRandomArray(31);
  let tree = list.reduce(insert, null);
  console.log(isBalanced(tree));
  visualize(tree, document.querySelector('#container'));
};

window.onload = main;
