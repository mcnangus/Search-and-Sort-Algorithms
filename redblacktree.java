import java.util.ArrayList;
import java.util.Collections;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

public class RedBlackTree {
	private Node root; // The root node of the tree
    private ArrayList<Integer> keyList;
    private ArrayList<Integer> idList;

    public class Node {
        Colour colour;       // Node colour
        int key;
        int id;
        int value;             // Node value
        Node parent;      // Parent node
        Node l, r;        // Children nodes
        int sum;
        int maxSum;
        int pmo;

        // Value node
        public Node(int key, int value, int id) {
        	this.key = key;
            this.value = value;
            this.colour = Colour.RED;
            this.parent = null;
            this.id = id;
            

            // Initialise children leaf nodes
            this.l = new Node();
            this.r = new Node();
            this.l.parent = this;
            this.r.parent = this;
            
            this.sum =  this.l.sum + this.value + this.r.sum;
            this.maxSum = Math.max(Math.max(this.l.maxSum, this.l.sum + this.value), this.l.sum+this.value+this.r.maxSum);
            if (this.maxSum == this.l.maxSum) {
            	this.pmo = this.l.pmo;
            } else if (this.maxSum == this.l.sum + this.value) {
            	this.pmo = this.key;
            } else {
            	this.pmo = this.r.pmo;
            }
        }

        // Leaf node
        public Node() {
            this.value = 0;
            this.colour = Colour.BLACK;
        }

        // Insert node into tree, ignoring colour
        public void insert(Node n) {        	
        	if (key > n.key) {
        		if (l.value == 0) {
        			l = n;
        			n.parent = this;
        		} else {
        			l.insert(n);
        		}
        	} else if (key < n.key) {
        		if (r.value == 0) {
        			r=n;
        			n.parent=this;
        		} else {
        			r.insert(n);
        		}
        	}
        }

        // Rotate the node so it becomes the child of its right branch
        public void rotateLeft() {
            // Make parent (if it exists) and right branch point to each other
            if (parent != null) {
                // Determine whether this node is the left or right child of its parent
                if (parent.l.key == key) {
                    parent.l = r;
                } else {
                    parent.r = r;
                }
            }
            r.parent = parent;

            parent = r;
            // Take right node's left branch
            r = parent.l;
            r.parent = this;
            // Take the place of the right node's left branch
            parent.l = this;
        }

        // Rotate the node so it becomes the child of its left branch
        public void rotateRight() {
        	// Make parent (if it exists) and left branch point to each other
            if (parent != null) {
                // Determine whether this node is the left or right child of its parent
                if (parent.l.key == key) {
                    parent.l = l;
                } else {
                    parent.r = l;
                }
            }
            l.parent = parent;

            parent = l;
            // Take left node's right branch
            l= parent.r;
            l.parent = this;
            // Take the place of the left node's right branch
            parent.r = this;
        }

    }

    // Initialise empty RBTree
    public RedBlackTree() {
        root = null;
        keyList = new ArrayList<Integer>();
        idList = new ArrayList<Integer>();
    }


    // Insert node into RBTree
    private void insert(Node x) {
        // You need only finish cases 1, 2 and 3; the rest has been done for you
    	
        // Insert node into tree
        if (root == null) {
            root = x;
        } else {
            root.insert(x);
            
        }

        // Fix tree
        while (x.key != root.key && x.parent.colour == Colour.RED) {
            boolean left = x.parent == x.parent.parent.l; // Is parent a left node
            Node y = left ? x.parent.parent.r : x.parent.parent.l; // Get opposite "uncle" node to parent

            if (y.colour == Colour.RED) {
                // Case 1: Recolour
            	x.parent.colour = Colour.BLACK;
            	y.colour = Colour.BLACK;
            	x.parent.parent.colour = Colour.RED;

                // Check if violated further up the tree
                x = x.parent.parent;
            } else {
                if (x.key == (left ? x.parent.r.key : x.parent.l.key)) {
                    // Case 2 : Left (uncle is left node) / Right (uncle is right node) Rotation
                    x = x.parent;
                    if (left) {
                        // Perform left rotation
                        if (x.key == root.key) root = x.r; // Update root
                        x.rotateLeft();
                    } else {
                        // This is part of the "then" clause where left and right are swapped
                         // Perform right rotation
                    	if (x.key == root.key) root = x.l; // Update root
                        x.rotateRight();
                    }

                }
                // Adjust colours to ensure correctness after rotation
                x.parent.colour = Colour.BLACK;
                x.parent.parent.colour = Colour.RED;
                // Case 3 : Right (uncle is left node) / Left (uncle is right node) Rotation
                    if (left) {
                        // Perform right rotation
                    	if (x.parent.parent.key == root.key) root = root.l;
                    	x.parent.parent.rotateRight();
                    } else
                    {
                        // This is part of the "then" clause where left and right are swapped
                        // Perform left rotation
                    	if (x.parent.parent.key == root.key) root = root.r;
                    	x.parent.parent.rotateLeft();
                    }
            
            }
        }

        // Ensure property 2 (root and leaves are black) holds
        
        root.colour = Colour.BLACK;
    }


    // (Safely) insert a value into the tree
    public void insert(int key, int value, int id) {
    	if (keyList.contains(key)) {
    		search(key).value += value;
    	} else {
    		keyList.add(key);
    		idList.add(id);
    		Node node = new Node(key, value, id);
    		if (node != null)
    			insert(node);
    	}
    }

    // Return the result of a pre-order transversal of the tree
    private void preOrder(Node tree) {
        if(tree != null && tree.value != 0) {
            System.out.print("("+tree.key + ", " + tree.value +", "+tree.colour+", "+tree.id+", "+tree.sum+", "+tree.maxSum+", "+tree.pmo+") ");
            preOrder(tree.l);
            preOrder(tree.r);
        }
    }

    public void preOrder() {
        preOrder(root);
        System.out.println();
    }

    // Return the corresponding node of a value, if it exists in the tree
    private Node find(Node x, int k) {
        if (x.key == 0)
            return null;

        if (k < x.key)
            return find(x.l, k);
        else if (k > x.key)
            return find(x.r, k);
        else
            return x;
    }

    public Node search(int key) {
        return find(root, key);
    }


    public enum Colour {
        RED,
        BLACK;
    }


	public void order() {
		Collections.sort(keyList);
		for (Integer i: keyList) {
			System.out.print(i+" ");
		}
		System.out.println();
	}
	
	public void getIDs() {
		Collections.sort(idList);
		for (Integer i: idList) {
			System.out.print(i+" ");
		}
		System.out.println();
	}
	
	public int PMO() {
		return root.pmo;
	}
	
	public int maxSum() {
		return root.maxSum;
	}
	
	public static void main(String[] args) {
        RedBlackTree tree = new RedBlackTree();
        
        if (args.length == 1) {
        	BufferedReader reader;
    		try {
    			reader = new BufferedReader(new FileReader(args[0]));
    			String line = reader.readLine();
    			while (line != null) {
    				String[] nums = line.split(" ");
    				if (nums.length != 1) {
    					tree.insert(Integer.parseInt(nums[1]), 1, Integer.parseInt(nums[0]));
    					tree.insert(Integer.parseInt(nums[2]), -1, Integer.parseInt(nums[0]));
    				}
    				line = reader.readLine();
    			}
    			reader.close();
    		} catch (IOException e) {
    			e.printStackTrace();
    		}
    		
    		System.out.println(tree.PMO() + " " + tree.maxSum());
            tree.getIDs();
            
        } else {
        	System.out.println("Please enter a valid filename when executing.");
        }
    }
}
