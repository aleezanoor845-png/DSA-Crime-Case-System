/*
================================================================================
                             CrimeSystem.h
================================================================================
*/

#ifndef CRIME_SYSTEM_H
#define CRIME_SYSTEM_H

#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <cmath>
#include <iomanip>
#include <sstream>   
#include <cctype>    
#include <limits>

using namespace std;

/*
================================================================================
                        ANSI COLOR CODE DEFINITIONS
================================================================================
*/
namespace Colors {
    const string RESET = "\033[0m";
    const string BOLD = "\033[1m";
    const string DIM = "\033[2m";
    const string UNDERLINE = "\033[4m";

    // Pastel foreground colors
    const string RED = "\033[91m";
    const string GREEN = "\033[92m";
    const string YELLOW = "\033[93m";
    const string BLUE = "\033[94m";
    const string MAGENTA = "\033[95m";
    const string CYAN = "\033[96m";
    const string WHITE = "\033[97m";

    // Pastel background colors
    const string BG_RED = "\033[101m";
    const string BG_GREEN = "\033[102m";
    const string BG_YELLOW = "\033[103m";
    const string BG_BLUE = "\033[104m";
    const string BG_MAGENTA = "\033[105m";
    const string BG_CYAN = "\033[106m";
    const string BG_WHITE = "\033[107m";

    // Custom pastel combinations
    const string HEADER = "\033[1;96m";      // Bold Cyan
    const string SUBHEADER = "\033[1;95m";   // Bold Magenta
    const string SUCCESS = "\033[1;92m";     // Bold Green
    const string WARNING = "\033[1;93m";     // Bold Yellow
    const string ERROR = "\033[1;91m";       // Bold Red
    const string INFO = "\033[1;94m";        // Bold Blue
    const string MENU_ITEM = "\033[96m";     // Cyan
    const string INPUT_PROMPT = "\033[93m";  // Yellow
    const string DATA_FIELD = "\033[95m";    // Magenta
    const string BORDER = "\033[90m";        // Gray
}

/*
================================================================================
                        CRIME TYPE ENUMERATION
================================================================================
*/
enum class CrimeType { 
    THEFT,
    ASSAULT,
    BURGLARY,
    FRAUD,
    VANDALISM,
    ROBBERY,
    HOMICIDE,
    KIDNAPPING,
    CYBERCRIME,
    DRUG_OFFENSE,
    ARSON,
    OTHER
};

/*
================================================================================
                        INVESTIGATION STATUS ENUMERATION
================================================================================
*/
enum class InvestigationStatus {
    PENDING,
    IN_PROGRESS,
    UNDER_REVIEW,
    CLOSED,
    COLD_CASE
};

/*
================================================================================
                        EVIDENCE TYPE ENUMERATION
================================================================================
*/
enum class EvidenceType {
    PHYSICAL,
    DIGITAL,
    DOCUMENTARY,
    TESTIMONIAL,
    FORENSIC,
    CIRCUMSTANTIAL
};

/*
================================================================================
                        UTILITY FUNCTIONS DECLARATIONS
================================================================================
*/
string crimeTypeToString(CrimeType type);
CrimeType stringToCrimeType(const string& str);
string statusToString(InvestigationStatus status);
string evidenceTypeToString(EvidenceType type);
string getCurrentDateTime();
int generateCaseID();

/*
================================================================================
                        CRIME RECORD STRUCTURE
================================================================================
*/
struct CrimeRecord {
    int caseID;                          // Unique identifier (used as AVL key)
    string crimeTitle;                   // Brief title of the crime
    CrimeType crimeType;                 // Category of crime
    string description;                  // Detailed description
    string location;                     // Crime location
    string dateReported;                 // Date when crime was reported
    string dateOccurred;                 // Date when crime occurred
    string reportedBy;                   // Name of person who reported
    string suspectName;                  // Primary suspect name
    string victimName;                   // Victim name
    InvestigationStatus status;          // Current investigation status
    string assignedOfficer;              // Officer handling the case
    int priorityLevel;                   // 1-10 priority scale
    string notes;                        // Additional notes

    // Default constructor
    CrimeRecord();

    // Parameterized constructor
    CrimeRecord(int id, const string& title, CrimeType type,
        const string& desc, const string& loc);

    // Display function for formatted output
    void display() const;

    // Comparison operators for AVL Tree operations
    bool operator<(const CrimeRecord& other) const;
    bool operator>(const CrimeRecord& other) const;
    bool operator==(const CrimeRecord& other) const;
    bool operator<=(const CrimeRecord& other) const;
    bool operator>=(const CrimeRecord& other) const;
};

/*
================================================================================
                        EVIDENCE STRUCTURE
================================================================================
*/
struct Evidence {
    int evidenceID;                      // Unique evidence identifier
    int relatedCaseID;                   // Link to crime case
    EvidenceType type;                   // Type of evidence
    string description;                  // Description of evidence
    string collectedBy;                  // Officer who collected
    string dateCollected;                // Collection date
    string storageLocation;              // Where evidence is stored
    bool isProcessed;                    // Whether evidence has been processed

    // Default constructor
    Evidence();

    // Parameterized constructor
    Evidence(int id, int caseID, EvidenceType t, const string& desc);

    // Display function
    void display() const;
};

/*
================================================================================
                        INVESTIGATION WORKFLOW ITEM
================================================================================
*/
struct InvestigationItem {
    int caseID;                          // Reference to crime case
    string caseTitle;                    // Brief title for display
    InvestigationStatus status;          // Current status
    string assignedOfficer;              // Officer assigned
    string dateQueued;                   // When added to queue
    int priority;                        // Priority level

    // Default constructor
    InvestigationItem();

    // Parameterized constructor
    InvestigationItem(int id, const string& title, const string& officer);

    // Display function
    void display() const;
};

/*
================================================================================
                    AVL TREE NODE TEMPLATE
================================================================================
*/

template <typename T>
struct AVLNode {
    T data;                              // Stored data element
    AVLNode<T>* left;                    // Left child pointer
    AVLNode<T>* right;                   // Right child pointer
    int height;                          // Height

    // Constructor:
    AVLNode(const T& value) : data(value), left(nullptr), right(nullptr), height(1) {}

    // Destructor:
    ~AVLNode() {
        left = nullptr;
        right = nullptr;
    }
};

/*       
================================================================================
                    AVL TREE TEMPLATE CLASS
================================================================================
*/
template <typename T>
class AVLTree {
private:
    AVLNode<T>* root;                    // Root node pointer
    int nodeCount;                       // Total number of nodes

    /*
    ========================================
            PRIVATE HELPER FUNCTIONS
        These implement core AVL logic
    ========================================
    */

    // Get height of a node (returns 0 for null)
    int getHeight(AVLNode<T>* node) const;

    // Calculate balance factor of a node
    int getBalanceFactor(AVLNode<T>* node) const;

    // Update height of a node based on children
    void updateHeight(AVLNode<T>* node);

    // Get maximum of two integers
    int max(int a, int b) const;

    /*
    ========================================
            AVL ROTATION OPERATIONS
    ========================================
    */
    // Right Rotation (LL Case)
    AVLNode<T>* rotateRight(AVLNode<T>* y);
    // Left Rotation (RR Case)
    AVLNode<T>* rotateLeft(AVLNode<T>* x);

    /*
    ========================================
            RECURSIVE CORE OPERATIONS
    ========================================
    */

   
    AVLNode<T>* insertNode(AVLNode<T>* node, const T& value);
    AVLNode<T>* findMin(AVLNode<T>* node) const;
    AVLNode<T>* findMax(AVLNode<T>* node) const;
    AVLNode<T>* deleteNode(AVLNode<T>* node, int key);
    AVLNode<T>* searchNode(AVLNode<T>* node, int key) const;
    void destroyTree(AVLNode<T>* node);

    /*
    ========================================
            TRAVERSAL HELPERS
        Store results in vector for reports
    ========================================
    */
    void inorderHelper(AVLNode<T>* node, vector<T>& result) const;
    void preorderHelper(AVLNode<T>* node, vector<T>& result) const;
    void postorderHelper(AVLNode<T>* node, vector<T>& result) const;
    void displayTreeHelper(AVLNode<T>* node, int level, string prefix) const;

public:
    /*
    ========================================
            CONSTRUCTOR & DESTRUCTOR
    ========================================
    */

    // Default constructor
    AVLTree();

    // Destructor - cleans up all allocated nodes
    ~AVLTree();

    /*
    ========================================
            PUBLIC INTERFACE
    ========================================
    */
    void insert(const T& value);
    bool remove(int key);
    T* search(int key);
    bool isEmpty() const;
    int size() const;
    int height() const;
    void clear();

    /*
    ========================================
            TRAVERSAL OPERATIONS
    ========================================
    */
    vector<T> inorderTraversal() const;
    vector<T> preorderTraversal() const;
    vector<T> postorderTraversal() const;
    void displayTree() const;
    AVLNode<T>* getRoot() const;
};

/*
================================================================================
                    QUEUE NODE TEMPLATE
================================================================================
*/
template <typename T>
struct QueueNode {
    T data;                              // Stored data element
    QueueNode<T>* next;                  // Pointer to next node

    // Constructor
    QueueNode(const T& value) : data(value), next(nullptr) {}
};

/*
================================================================================
                    LINKED LIST QUEUE TEMPLATE CLASS
================================================================================
*/
template <typename T>
class LinkedQueue {
private:
    QueueNode<T>* front;                 // Front of queue (dequeue here)
    QueueNode<T>* rear;                  // Rear of queue (enqueue here)
    int count;                           // Number of elements

public:
    // Constructor
    LinkedQueue();

    // Destructor - cleans up all nodes
    ~LinkedQueue();

    void enqueue(const T& value);
    T dequeue();
    T peek() const;
    bool isEmpty() const;
    int size() const;
    void clear();
    void display() const;
    vector<T> getAllElements() const;
};

/*
================================================================================
                    CIRCULAR QUEUE TEMPLATE CLASS
================================================================================
*/
template <typename T>
class CircularQueue {
private:
    T* array;                            // Dynamic array for storage
    int capacity;                        // Maximum capacity
    int frontIndex;                      // Index of front element
    int rearIndex;                       // Index of rear element
    int count;                           // Current number of elements

public:
    // Constructor with capacity
    CircularQueue(int cap = 100);

    // Destructor
    ~CircularQueue();

    
    bool enqueue(const T& value);
    T dequeue();
    T peek() const;
    bool isEmpty() const;
    bool isFull() const;
    int size() const;
    int getCapacity() const;
    void clear();
    void display() const;
};

/*
================================================================================
                    STACK NODE TEMPLATE
================================================================================
*/
template <typename T>
struct StackNode {
    T data;                              // Stored data element
    StackNode<T>* next;                  // Pointer to next node (below in stack)

    // Constructor
    StackNode(const T& value) : data(value), next(nullptr) {}

    // Destructor
    ~StackNode() {
        next = nullptr;
    }
};

/*
================================================================================
                    LINKED STACK TEMPLATE CLASS
================================================================================
*/
template <typename T>
class LinkedStack {
private:
    StackNode<T>* top;                   // Top of stack
    int count;                           // Number of elements

public:
    // Constructor
    LinkedStack();

    // Destructor
    ~LinkedStack();
    void push(const T& value);
    T pop();
    T peek() const;
    bool isEmpty() const;
    int size() const;
    void clear();
    void display() const;
};

/*
================================================================================
                    EXPRESSION EVALUATOR CLASS
================================================================================
*/
class ExpressionEvaluator {
private:
    bool isOperator(char c) const;

    // Get operator precedence
    // Higher value = higher precedence
    int getPrecedence(char op) const;

    // Check if character is operand (digit)
    bool isOperand(char c) const;

    // Perform arithmetic operation
    double performOperation(double a, double b, char op) const;

public:
    // Default constructor
    ExpressionEvaluator();
    string infixToPostfix(const string& infix);
    double evaluatePostfix(const string& postfix);
    string decimalToBinary(int decimal);
    double evaluateInfix(const string& infix);
    bool validateExpression(const string& expr) const;
};

/*
================================================================================
                    SORTING ALGORITHMS CLASS
================================================================================
*/
class SortingAlgorithms {
private:
    static int partition(vector<CrimeRecord>& arr, int low, int high);

    // Quick Sort recursive helper
    static void quickSortHelper(vector<CrimeRecord>& arr, int low, int high);

    // Merge Sort merge helper
    static void merge(vector<CrimeRecord>& arr, int left, int mid, int right);

    // Merge Sort recursive helper
    static void mergeSortHelper(vector<CrimeRecord>& arr, int left, int right);

public:
    /*
    ========================================
        INSERTION SORT

    ========================================
    */
    static void insertionSort(vector<CrimeRecord>& arr);

    /*
    ========================================
        QUICK SORT
    ========================================
    */
    static void quickSort(vector<CrimeRecord>& arr);

    /*
    ========================================
        MERGE SORT
    ========================================
    */
    static void mergeSort(vector<CrimeRecord>& arr);

    // Sort by different criteria
    static void sortByCaseID(vector<CrimeRecord>& arr, const string& algorithm);
    static void sortByPriority(vector<CrimeRecord>& arr, const string& algorithm);
    static void sortByDate(vector<CrimeRecord>& arr, const string& algorithm);
};

/*
================================================================================
                    SEARCHING ALGORITHMS CLASS
================================================================================
*/
class SearchingAlgorithms {
public:
    /*
    ========================================
        LINEAR SEARCH
    ========================================
    */
    static int linearSearch(const vector<CrimeRecord>& arr, int caseID);

    /*
    ========================================
        BINARY SEARCH
    ========================================
    */
    static int binarySearch(const vector<CrimeRecord>& arr, int caseID);

    // Search by different criteria
    static vector<CrimeRecord> searchByCrimeType(const vector<CrimeRecord>& arr, CrimeType type);
    static vector<CrimeRecord> searchByStatus(const vector<CrimeRecord>& arr, InvestigationStatus status);
    static vector<CrimeRecord> searchByLocation(const vector<CrimeRecord>& arr, const string& location);
    static vector<CrimeRecord> searchByDateRange(const vector<CrimeRecord>& arr,
        const string& startDate, const string& endDate);
};

/*
================================================================================
                    CRIME STATISTICS STRUCTURE
================================================================================
*/
struct CrimeStatistics {
    int totalCrimes;
    int pendingCases;
    int inProgressCases;
    int closedCases;
    int coldCases;

    // Crime type counts
    int theftCount;
    int assaultCount;
    int burglaryCount;
    int fraudCount;
    int vandalismCount;
    int robberyCount;
    int homicideCount;
    int kidnappingCount;
    int cybercrimeCount;
    int drugOffenseCount;
    int arsonCount;
    int otherCount;

    // Priority distribution
    int highPriority;     // 8-10
    int mediumPriority;   // 4-7
    int lowPriority;      // 1-3

    // Constructor
    CrimeStatistics();

    // Reset all values
    void reset();

    // Display statistics
    void display() const;
};

/*
================================================================================
                    REPORTING MODULE CLASS
================================================================================
*/
class ReportingModule {
private:
    // Helper for bar chart display
    static void printBar(int count, int maxCount, int barWidth);

public:
    // Generate statistics from crime records
    static CrimeStatistics generateStatistics(const vector<CrimeRecord>& records);

    // Display all records in formatted table
    static void displayAllRecords(const vector<CrimeRecord>& records);

    // Display records by crime type
    static void displayByCrimeType(const vector<CrimeRecord>& records);

    // Display records by status
    static void displayByStatus(const vector<CrimeRecord>& records);

    // Display priority distribution chart
    static void displayPriorityChart(const CrimeStatistics& stats);

    // Display crime type distribution chart
    static void displayCrimeTypeChart(const CrimeStatistics& stats);

    // Export report to string format
    static string generateTextReport(const vector<CrimeRecord>& records,
        const CrimeStatistics& stats);

    // Compare search algorithms performance
    static void compareSearchAlgorithms(const vector<CrimeRecord>& records, int searchKey);

    // Compare sorting algorithms performance
    static void compareSortingAlgorithms(vector<CrimeRecord> records);
};

/*
================================================================================
                    ALGORITHM ANALYSIS DISPLAY CLASS
================================================================================
*/
class AlgorithmAnalysis {
public:
    // Display AVL Tree complexity analysis
    static void displayAVLComplexity();

    // Display Queue complexity analysis
    static void displayQueueComplexity();

    // Display Stack complexity analysis
    static void displayStackComplexity();

    // Display Sorting algorithms complexity
    static void displaySortingComplexity();

    // Display Searching algorithms complexity
    static void displaySearchingComplexity();

    // Display complete analysis
    static void displayFullAnalysis();

    // Display comparison table
    static void displayComparisonTable();

    // Display why each DS was chosen
    static void displayDesignDecisions();
};

/*
================================================================================
                    UI MODULE CLASS
================================================================================
*/
class UIModule {
private:
    // Clear screen (cross-platform)
    static void clearScreen();

    // Wait for user input
    static void waitForEnter();

    // Print horizontal line
    static void printLine(char c = '-', int width = 70);

    // Print centered text
    static void printCentered(const string& text, int width = 70);

    // Print header box
    static void printHeader(const string& title);

    // Validate integer input
    static bool getIntInput(int& value, const string& prompt, int min, int max);

    // Validate string input
    static bool getStringInput(string& value, const string& prompt, bool allowEmpty = false);

public:
    // Display main menu
    static void displayMainMenu();

    // Display crime record submenu
    static void displayCrimeRecordMenu();

    // Display investigation submenu
    static void displayInvestigationMenu();

    // Display evidence submenu
    static void displayEvidenceMenu();

    // Display reporting submenu
    static void displayReportingMenu();

    // Display algorithm analysis submenu
    static void displayAlgorithmMenu();

    // Display welcome screen
    static void displayWelcome();

    // Display goodbye screen
    static void displayGoodbye();

    // Get crime type from user
    static CrimeType getCrimeTypeInput();

    // Get investigation status from user
    static InvestigationStatus getStatusInput();

    // Get evidence type from user
    static EvidenceType getEvidenceTypeInput();

    // Input crime record details
    static CrimeRecord inputCrimeRecord();

    // Input evidence details
    static Evidence inputEvidence(int caseID);

    // Display error message
    static void displayError(const string& message);

    // Display success message
    static void displaySuccess(const string& message);

    // Display warning message
    static void displayWarning(const string& message);

    // Display info message
    static void displayInfo(const string& message);

    // Get menu choice
    static int getMenuChoice(int min, int max);

    // Confirm action
    static bool confirmAction(const string& message);
};

/*
================================================================================
                    CRIME SYSTEM MANAGER CLASS
================================================================================
*/
class CrimeSystemManager {
private:
    AVLTree<CrimeRecord> crimeTree;              // Primary crime record storage
    LinkedQueue<InvestigationItem> investigationQueue;  // Investigation workflow
    LinkedStack<Evidence> evidenceStack;          // Evidence handling
    CircularQueue<string> recentActions;          // Activity log (circular)
    ExpressionEvaluator evaluator;                // Expression evaluation

    // Note: Case/Evidence IDs are managed by global counters in CrimeSystem.cpp

    // Log an action
    void logAction(const string& action);

public:
    // Constructor
    CrimeSystemManager();

    // Destructor
    ~CrimeSystemManager();

    /*
    ========================================
        CRIME RECORD OPERATIONS
        Uses AVL Tree
    ========================================
    */

    // Register new crime
    void registerCrime();

    // Search crime by ID
    void searchCrime();

    // Update crime record
    void updateCrime();

    // Delete crime record
    void deleteCrime();

    // View all crimes
    void viewAllCrimes();

    // View crimes by traversal type
    void viewByTraversal();

    // Display AVL tree structure
    void displayCrimeTree();

    /*
    ========================================
        INVESTIGATION OPERATIONS
        Uses Queue
    ========================================
    */

    // Add to investigation queue
    void addToInvestigation();

    // Process next investigation
    void processNextInvestigation();

    // View investigation queue
    void viewInvestigationQueue();

    // Check queue status
    void checkQueueStatus();

    /*
    ========================================
        EVIDENCE OPERATIONS
        Uses Stack
    ========================================
    */

    // Add evidence
    void addEvidence();

    // Process evidence (pop from stack)
    void processEvidence();

    // View evidence stack
    void viewEvidenceStack();

    // Analyze evidence (expression evaluation)
    void analyzeEvidence();

    // Convert analysis values
    void convertValues();

    /*
    ========================================
        REPORTING OPERATIONS
    ========================================
    */

    // Generate full report
    void generateReport();

    // Generate statistics
    void generateStatistics();

    // Search crimes by criteria
    void searchCrimesByCriteria();

    // Sort and display records
    void sortAndDisplay();

    // Compare algorithms
    void compareAlgorithms();

    /*
    ========================================
        ALGORITHM ANALYSIS
    ========================================
    */

    // Display DS complexities
    void displayComplexities();

    // Display design decisions
    void displayDesignDecisions();

    /*
    ========================================
        SYSTEM OPERATIONS
    ========================================
    */

    // View recent actions
    void viewRecentActions();

    // Run the main system loop
    void run();

    // Handle main menu
    void handleMainMenu();

    // Handle crime record menu
    void handleCrimeRecordMenu();

    // Handle investigation menu
    void handleInvestigationMenu();

    // Handle evidence menu
    void handleEvidenceMenu();

    // Handle reporting menu
    void handleReportingMenu();

    // Handle algorithm menu
    void handleAlgorithmMenu();

    // Add sample data for testing
    void addSampleData();
};

/*
================================================================================
                    TEMPLATE IMPLEMENTATIONS
================================================================================

================================================================================
                     AVL TREE TEMPLATE IMPLEMENTATION
================================================================================
*/

// Constructor
template <typename T>
AVLTree<T>::AVLTree() : root(nullptr), nodeCount(0) {}

// Destructor
template <typename T>
AVLTree<T>::~AVLTree() {
    destroyTree(root);
}

// Get height of node
template <typename T>
int AVLTree<T>::getHeight(AVLNode<T>* node) const {
    if (node == nullptr)
    {
        return 0;
    }
    return node->height;
}

// Get balance factor
template <typename T>
int AVLTree<T>::getBalanceFactor(AVLNode<T>* node) const {
    if (node == nullptr)
    {
        return 0;
    }
    return getHeight(node->left) - getHeight(node->right);
}

// Update height
template <typename T>
void AVLTree<T>::updateHeight(AVLNode<T>* node) {
    if (node != nullptr) {
        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    }
}

// Max helper
template <typename T>
int AVLTree<T>::max(int a, int b) const {
    return (a > b) ? a : b;
}

// Right Rotation (LL Case)
template <typename T>
AVLNode<T>* AVLTree<T>::rotateRight(AVLNode<T>* y) {
    AVLNode<T>* x = y->left;
    AVLNode<T>* T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights (order matters)
    updateHeight(y);
    updateHeight(x);

    // Return new root
    return x;
}

// Left Rotation (RR Case)
template <typename T>
AVLNode<T>* AVLTree<T>::rotateLeft(AVLNode<T>* y) {
    AVLNode<T>* x = y->right;
    AVLNode<T>* T2 = x->left;

    // Perform rotation
    x->left = y;
    y->right = T2;

    // Update heights (order matters)
    updateHeight(y);
    updateHeight(x);

    // Return new root
    return x;
}

// Insert node with balancing
// Complexity: O(log n) due to balanced tree
template <typename T>
AVLNode<T>* AVLTree<T>::insertNode(AVLNode<T>* node, const T& value) {
    // Standard BST insertion
    if (node == nullptr) {
        nodeCount++;
        return new AVLNode<T>(value);
    }

    if (value < node->data) {
        node->left = insertNode(node->left, value);
    }
    else if (value > node->data) {
        node->right = insertNode(node->right, value);
    }
    else {
        // Duplicate keys not allowed
        return node;
    }

    // Update height of ancestor node
    updateHeight(node);

    // Get balance factor to check if unbalanced
    int balance = getBalanceFactor(node);

    // Left Left Case (LL)
    if (balance > 1 && value < node->left->data) {
        return rotateRight(node);
    }

    // Right Right Case (RR)
    if (balance < -1 && value > node->right->data) {
        return rotateLeft(node);
    }

    // Left Right Case (LR)
    if (balance > 1 && value > node->left->data) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    // Right Left Case (RL)
    if (balance < -1 && value < node->right->data) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

// Find minimum value node
template <typename T>
AVLNode<T>* AVLTree<T>::findMin(AVLNode<T>* node) const {
    AVLNode<T>* current = node;
    while (current && current->left != nullptr) {
        current = current->left;
    }
    return current;
}

// Find maximum value node
template <typename T>
AVLNode<T>* AVLTree<T>::findMax(AVLNode<T>* node) const {
    AVLNode<T>* current = node;
    while (current && current->right != nullptr) {
        current = current->right;
    }
    return current;
}

// Delete node with balancing
// Complexity: O(log n)
template <typename T>
AVLNode<T>* AVLTree<T>::deleteNode(AVLNode<T>* node, int key) {
    if (node == nullptr) 
        return nullptr;
    // Standard BST deletion
    if (key < node->data.caseID) {
        node->left = deleteNode(node->left, key);
    }
    else if (key > node->data.caseID) {
        node->right = deleteNode(node->right, key);
    }
    else {
        // Node to delete found

        // Node with one child or no child
        if (node->left == nullptr || node->right == nullptr) {
            AVLNode<T>* temp = node->left ? node->left : node->right;

            if (temp == nullptr) {
                // No child case
                temp = node;
                node = nullptr;
            }
            else {
                // One child case
                *node = *temp;
            }
            delete temp;
            nodeCount--;
        }
        else {
            // Node with two children
            // Get inorder successor (smallest in right subtree)
            AVLNode<T>* temp = findMin(node->right);
            node->data = temp->data;
            node->right = deleteNode(node->right, temp->data.caseID);
        }
    }

    if (node == nullptr) return nullptr;

    // Update height
    updateHeight(node);

    // Get balance factor
    int balance = getBalanceFactor(node);

    // Left Left Case
    if (balance > 1 && getBalanceFactor(node->left) >= 0) {
        return rotateRight(node);
    }

    // Left Right Case
    if (balance > 1 && getBalanceFactor(node->left) < 0) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    // Right Right Case
    if (balance < -1 && getBalanceFactor(node->right) <= 0) {
        return rotateLeft(node);
    }

    // Right Left Case
    if (balance < -1 && getBalanceFactor(node->right) > 0) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

// Search for node by key
// Complexity: O(log n)
template <typename T>
AVLNode<T>* AVLTree<T>::searchNode(AVLNode<T>* node, int key) const {
    if (node == nullptr || node->data.caseID == key) {
        return node;
    }

    if (key < node->data.caseID) {
        return searchNode(node->left, key);
    }
    return searchNode(node->right, key);
}

// Destroy tree recursively
template <typename T>
void AVLTree<T>::destroyTree(AVLNode<T>* node) {
    if (node != nullptr) {
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }
}

// Inorder traversal helper
// Left -> Root -> Right produces sorted output
template <typename T>
void AVLTree<T>::inorderHelper(AVLNode<T>* node, vector<T>& result) const {
    if (node != nullptr) {
        inorderHelper(node->left, result);
        result.push_back(node->data);
        inorderHelper(node->right, result);
    }
}

// Preorder traversal helper
// Root -> Left -> Right
template <typename T>
void AVLTree<T>::preorderHelper(AVLNode<T>* node, vector<T>& result) const {
    if (node != nullptr) {
        result.push_back(node->data);
        preorderHelper(node->left, result);
        preorderHelper(node->right, result);
    }
}

// Postorder traversal helper
// Left -> Right -> Root
template <typename T>
void AVLTree<T>::postorderHelper(AVLNode<T>* node, vector<T>& result) const {
    if (node != nullptr) {
        postorderHelper(node->left, result);
        postorderHelper(node->right, result);
        result.push_back(node->data);
    }
}

// Display tree structure
template <typename T>
void AVLTree<T>::displayTreeHelper(AVLNode<T>* node, int level, string prefix) const {
    if (node != nullptr) {
        cout << prefix;
        cout << (level == 0 ? "ROOT: " : "+-- ");
        cout << Colors::CYAN << "Case #" << node->data.caseID
            << Colors::RESET << " (h=" << node->height
            << ", bf=" << getBalanceFactor(node) << ")" << endl;

        string newPrefix = prefix + (level == 0 ? "" : "|   ");

        if (node->left || node->right) //agar koi bhi child ho,recursion continue
        {
            if (node->right) {
                displayTreeHelper(node->right, level + 1, newPrefix);
            }
            if (node->left) {
                displayTreeHelper(node->left, level + 1, newPrefix);
            }
        }
    }
}

// Public insert
template <typename T>
void AVLTree<T>::insert(const T& value) {
    root = insertNode(root, value);
}

// Public remove
template <typename T>
bool AVLTree<T>::remove(int key) {
    if (searchNode(root, key) == nullptr)
    {
        return false;
    }
    root = deleteNode(root, key);
    return true;
}

// Public search
template <typename T>
T* AVLTree<T>::search(int key) {
    AVLNode<T>* result = searchNode(root, key);
    if (result != nullptr) {
        return &(result->data);  //returning data's address !
    }
    return nullptr;
}

// Check if empty
template <typename T>
bool AVLTree<T>::isEmpty() const {
    return root == nullptr;
}

// Get size
template <typename T>
int AVLTree<T>::size() const {
    return nodeCount;
}

// Get height
template <typename T>
int AVLTree<T>::height() const {
    return getHeight(root);
}

// Clear tree
template <typename T>
void AVLTree<T>::clear() {
    destroyTree(root);
    root = nullptr;
    nodeCount = 0;
}

// Inorder traversal
template <typename T>
vector<T> AVLTree<T>::inorderTraversal() const {
    vector<T> result;
    inorderHelper(root, result);
    return result;
}

// Preorder traversal
template <typename T>
vector<T> AVLTree<T>::preorderTraversal() const {
    vector<T> result;
    preorderHelper(root, result);
    return result;
}

// Postorder traversal
template <typename T>
vector<T> AVLTree<T>::postorderTraversal() const {
    vector<T> result;
    postorderHelper(root, result);
    return result;
}

// Display tree
template <typename T>
void AVLTree<T>::displayTree() const {
    if (root == nullptr) {
        cout << Colors::WARNING << "Tree is empty." << Colors::RESET << endl;
        return;
    }
    cout << Colors::HEADER << "\n=== AVL Tree Structure ===" << Colors::RESET << endl;
    displayTreeHelper(root, 0, "");
}

// Get root
template <typename T>
AVLNode<T>* AVLTree<T>::getRoot() const {
    return root;
}

/*
================================================================================
    LINKED QUEUE TEMPLATE IMPLEMENTATION
================================================================================
*/

// Constructor
template <typename T>
LinkedQueue<T>::LinkedQueue() : front(nullptr), rear(nullptr), count(0) {}

// Destructor
template <typename T>
LinkedQueue<T>::~LinkedQueue() {
    clear();
}

template <typename T>
void LinkedQueue<T>::enqueue(const T& value) {
    QueueNode<T>* newNode = new QueueNode<T>(value);

    if (isEmpty()) {
        front = rear = newNode;
    }
    else {
        rear->next = newNode;
        rear = newNode;
    }
    count++;
}

// Dequeue - O(1)
template <typename T>
T LinkedQueue<T>::dequeue() {
    if (isEmpty()) {
        throw runtime_error("Queue is empty - cannot dequeue");
    }

    QueueNode<T>* temp = front;
    T data = front->data;
    front = front->next;

    if (front == nullptr) {
        rear = nullptr;
    }

    delete temp;
    count--;
    return data;
}

// Peek - O(1)
template <typename T>
T LinkedQueue<T>::peek() const {
    if (isEmpty()) {
        throw runtime_error("Queue is empty - cannot peek");
    }
    return front->data;
}

// Check if empty
template <typename T>
bool LinkedQueue<T>::isEmpty() const {
    return front == nullptr;
}

// Get size
template <typename T>
int LinkedQueue<T>::size() const {
    return count;
}

// Clear queue
template <typename T>
void LinkedQueue<T>::clear() {
    while (!isEmpty()) {
        dequeue();
    }
}

// Display queue
template <typename T>
void LinkedQueue<T>::display() const {
    if (isEmpty()) {
        cout << Colors::WARNING << "Queue is empty." << Colors::RESET << endl;
        return;
    }

    cout << Colors::HEADER << "\n=== Queue Contents (Front to Rear) ===" << Colors::RESET << endl;
    QueueNode<T>* current = front;
    int position = 1;

    while (current != nullptr) {
        cout << Colors::INFO << "[" << position << "] " << Colors::RESET;
        current->data.display();
        current = current->next;
        position++;
    }
}

// Get all elements as vector
template <typename T>
vector<T> LinkedQueue<T>::getAllElements() const {
    vector<T> elements;
    QueueNode<T>* current = front;

    while (current != nullptr) {
        elements.push_back(current->data);
        current = current->next;
    }

    return elements;
}

/*
================================================================================
    CIRCULAR QUEUE TEMPLATE IMPLEMENTATION
================================================================================
*/

// Constructor
template <typename T>
CircularQueue<T>::CircularQueue(int cap)
    : capacity(cap), frontIndex(0), rearIndex(-1), count(0) {
    array = new T[capacity];
}

// Destructor
template <typename T>
CircularQueue<T>::~CircularQueue() {
    delete[] array;
}

// Enqueue - O(1)
template <typename T>
bool CircularQueue<T>::enqueue(const T& value) {
    if (isFull()) {
        return false;
    }

    rearIndex = (rearIndex + 1) % capacity;
    array[rearIndex] = value;
    count++;
    return true;
}

// Dequeue - O(1)
template <typename T>
T CircularQueue<T>::dequeue() {
    if (isEmpty()) {
        throw runtime_error("Circular queue is empty");
    }

    T data = array[frontIndex];
    frontIndex = (frontIndex + 1) % capacity;
    count--;
    return data;
}

// Peek - O(1)
template <typename T>
T CircularQueue<T>::peek() const {
    if (isEmpty()) {
        throw runtime_error("Circular queue is empty");
    }
    return array[frontIndex];
}

// Check if empty
template <typename T>
bool CircularQueue<T>::isEmpty() const {
    return count == 0;
}

// Check if full
template <typename T>
bool CircularQueue<T>::isFull() const {
    return count == capacity;
}

// Get size
template <typename T>
int CircularQueue<T>::size() const {
    return count;
}

// Get capacity
template <typename T>
int CircularQueue<T>::getCapacity() const {
    return capacity;
}

// Clear
template <typename T>
void CircularQueue<T>::clear() {
    frontIndex = 0;
    rearIndex = -1;
    count = 0;
}

// Display
template <typename T>
void CircularQueue<T>::display() const {
    if (isEmpty()) {
        cout << Colors::WARNING << "Circular queue is empty." << Colors::RESET << endl;
        return;
    }

    cout << Colors::HEADER << "\n=== Circular Queue Contents ===" << Colors::RESET << endl;
    int index = frontIndex;
    for (int i = 0; i < count; i++) {
        cout << Colors::INFO << "[" << (i + 1) << "] " << Colors::RESET;
        cout << array[index] << endl;
        index = (index + 1) % capacity;
    }
}

/*
================================================================================
    LINKED STACK TEMPLATE IMPLEMENTATION
================================================================================
*/

// Constructor
template <typename T>
LinkedStack<T>::LinkedStack() : top(nullptr), count(0) {}

// Destructor
template <typename T>
LinkedStack<T>::~LinkedStack() {
    clear();
}
template <typename T>
void LinkedStack<T>::push(const T& value) {
    StackNode<T>* newNode = new StackNode<T>(value);
    newNode->next = top;
    top = newNode;
    count++;
}

// Pop - O(1)
template <typename T>
T LinkedStack<T>::pop() {
    if (isEmpty()) {
        throw runtime_error("Stack is empty - cannot pop");
    }

    StackNode<T>* temp = top;
    T data = top->data;
    top = top->next;
    delete temp;
    count--;
    return data;
}

// Peek - O(1)
template <typename T>
T LinkedStack<T>::peek() const {
    if (isEmpty()) {
        throw runtime_error("Stack is empty - cannot peek");
    }
    return top->data;
}

// Check if empty
template <typename T>
bool LinkedStack<T>::isEmpty() const {
    return top == nullptr;
}

// Get size
template <typename T>
int LinkedStack<T>::size() const {
    return count;
}

// Clear stack
template <typename T>
void LinkedStack<T>::clear() {
    while (!isEmpty()) {
        pop();
    }
}

// Display stack
template <typename T>
void LinkedStack<T>::display() const {
    if (isEmpty()) {
        cout << Colors::WARNING << "Stack is empty." << Colors::RESET << endl;
        return;
    }

    cout << Colors::HEADER << "\n=== Stack Contents (Top to Bottom) ===" << Colors::RESET << endl;
    StackNode<T>* current = top;
    int position = 1;

    while (current != nullptr) {
        cout << Colors::INFO << "[" << position << "] " << Colors::RESET;
        current->data.display();
        current = current->next;
        position++;
    }
}

#endif // CRIME_SYSTEM_H

