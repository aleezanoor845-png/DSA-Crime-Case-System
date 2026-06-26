/*
===================================================
                CrimeSystem.cpp
===================================================
*/

#include "CrimeSystem.h"
#include <algorithm>
#include <cstring>

/*
================================================================================
                    GLOBAL VARIABLES
================================================================================
*/
static int globalCaseIDCounter = 1000;
static int globalEvidenceIDCounter = 5000;

/*
================================================================================
                    UTILITY FUNCTION IMPLEMENTATIONS
================================================================================
*/

// Convert CrimeType enum to string
string crimeTypeToString(CrimeType type) {
    switch (type) {
    case CrimeType::THEFT:        return "Theft";
    case CrimeType::ASSAULT:      return "Assault";
    case CrimeType::BURGLARY:     return "Burglary";
    case CrimeType::FRAUD:        return "Fraud";
    case CrimeType::VANDALISM:    return "Vandalism";
    case CrimeType::ROBBERY:      return "Robbery";
    case CrimeType::HOMICIDE:     return "Homicide";
    case CrimeType::KIDNAPPING:   return "Kidnapping";
    case CrimeType::CYBERCRIME:   return "Cybercrime";
    case CrimeType::DRUG_OFFENSE: return "Drug Offense";
    case CrimeType::ARSON:        return "Arson";
    case CrimeType::OTHER:        return "Other";
    default:                      return "Unknown";
    }
}

// Convert string to CrimeType enum
CrimeType stringToCrimeType(const string& str) {
    if (str == "Theft" || str == "1")        return CrimeType::THEFT;
    if (str == "Assault" || str == "2")      return CrimeType::ASSAULT;
    if (str == "Burglary" || str == "3")     return CrimeType::BURGLARY;
    if (str == "Fraud" || str == "4")        return CrimeType::FRAUD;
    if (str == "Vandalism" || str == "5")    return CrimeType::VANDALISM;
    if (str == "Robbery" || str == "6")      return CrimeType::ROBBERY;
    if (str == "Homicide" || str == "7")     return CrimeType::HOMICIDE;
    if (str == "Kidnapping" || str == "8")   return CrimeType::KIDNAPPING;
    if (str == "Cybercrime" || str == "9")   return CrimeType::CYBERCRIME;
    if (str == "Drug Offense" || str == "10") return CrimeType::DRUG_OFFENSE;
    if (str == "Arson" || str == "11")       return CrimeType::ARSON;
    return CrimeType::OTHER;
}

// Convert InvestigationStatus enum to string
string statusToString(InvestigationStatus status) {
    switch (status) {
    case InvestigationStatus::PENDING:      return "Pending";
    case InvestigationStatus::IN_PROGRESS:  return "In Progress";
    case InvestigationStatus::UNDER_REVIEW: return "Under Review";
    case InvestigationStatus::CLOSED:       return "Closed";
    case InvestigationStatus::COLD_CASE:    return "Cold Case";
    default:                                return "Unknown";
    }
}

// Convert EvidenceType enum to string
string evidenceTypeToString(EvidenceType type) {
    switch (type) {
    case EvidenceType::PHYSICAL:       return "Physical";
    case EvidenceType::DIGITAL:        return "Digital";
    case EvidenceType::DOCUMENTARY:    return "Documentary";
    case EvidenceType::TESTIMONIAL:    return "Testimonial";
    case EvidenceType::FORENSIC:       return "Forensic";
    case EvidenceType::CIRCUMSTANTIAL: return "Circumstantial";
    default:                           return "Unknown";
    }
}

// Get current date and time as string
string getCurrentDateTime() {
    time_t now = time(0);   
    struct tm timeinfo;
#ifdef _WIN32
    localtime_s(&timeinfo, &now);
#else
    localtime_r(&now, &timeinfo);
#endif
    char buffer[80];
    strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", &timeinfo);
    return string(buffer);
}

// Generate unique case ID
int generateCaseID() {
    return ++globalCaseIDCounter;
}

/*
================================================================================
                    CRIME RECORD IMPLEMENTATION
================================================================================
*/

// Default constructor
CrimeRecord::CrimeRecord()
    : caseID(0), crimeTitle(""), crimeType(CrimeType::OTHER),
    description(""), location(""), dateReported(""), dateOccurred(""),
    reportedBy(""), suspectName("Unknown"), victimName(""),
    status(InvestigationStatus::PENDING), assignedOfficer("Unassigned"),
    priorityLevel(5), notes("") {}

// Parameterized constructor
CrimeRecord::CrimeRecord(int id, const string& title, CrimeType type,
    const string& desc, const string& loc)
    : caseID(id), crimeTitle(title), crimeType(type),
    description(desc), location(loc), dateReported(getCurrentDateTime()),
    dateOccurred(""), reportedBy(""), suspectName("Unknown"),
    victimName(""), status(InvestigationStatus::PENDING),
    assignedOfficer("Unassigned"), priorityLevel(5), notes("") {}

// Display crime record
void CrimeRecord::display() const {
    cout << Colors::BORDER << "+--------------------------------------------------+" << Colors::RESET << endl;
    cout << Colors::HEADER << "  CASE #" << caseID << ": " << crimeTitle << Colors::RESET << endl;
    cout << Colors::BORDER << "+--------------------------------------------------+" << Colors::RESET << endl;
    cout << Colors::DATA_FIELD << "  Crime Type:      " << Colors::RESET << crimeTypeToString(crimeType) << endl;
    cout << Colors::DATA_FIELD << "  Status:          " << Colors::RESET << statusToString(status) << endl;
    cout << Colors::DATA_FIELD << "  Priority:        " << Colors::RESET << priorityLevel << "/10" << endl;
    cout << Colors::DATA_FIELD << "  Location:        " << Colors::RESET << location << endl;
    cout << Colors::DATA_FIELD << "  Date Reported:   " << Colors::RESET << dateReported << endl;
    cout << Colors::DATA_FIELD << "  Date Occurred:   " << Colors::RESET << (dateOccurred.empty() ? "Not specified" : dateOccurred) << endl;
    cout << Colors::DATA_FIELD << "  Reported By:     " << Colors::RESET << (reportedBy.empty() ? "Anonymous" : reportedBy) << endl;
    cout << Colors::DATA_FIELD << "  Victim:          " << Colors::RESET << (victimName.empty() ? "Not specified" : victimName) << endl;
    cout << Colors::DATA_FIELD << "  Suspect:         " << Colors::RESET << suspectName << endl;
    cout << Colors::DATA_FIELD << "  Officer:         " << Colors::RESET << assignedOfficer << endl;
    cout << Colors::DATA_FIELD << "  Description:     " << Colors::RESET << endl;
    cout << "    " << (description.empty() ? "No description provided" : description) << endl;
    if (!notes.empty()) {
        cout << Colors::DATA_FIELD << "  Notes:           " << Colors::RESET << endl;
        cout << "    " << notes << endl;
    }
    cout << Colors::BORDER << "+--------------------------------------------------+" << Colors::RESET << endl;
}

// Comparison operators for AVL Tree - compare by caseID
bool CrimeRecord::operator<(const CrimeRecord& other) const {
    return caseID < other.caseID;
}

bool CrimeRecord::operator>(const CrimeRecord& other) const {
    return caseID > other.caseID;
}

bool CrimeRecord::operator==(const CrimeRecord& other) const {
    return caseID == other.caseID;
}

bool CrimeRecord::operator<=(const CrimeRecord& other) const {
    return caseID <= other.caseID;
}

bool CrimeRecord::operator>=(const CrimeRecord& other) const {
    return caseID >= other.caseID;
}

/*
================================================================================
                    EVIDENCE IMPLEMENTATION
================================================================================
*/

// Default constructor
Evidence::Evidence()
    : evidenceID(0), relatedCaseID(0), type(EvidenceType::PHYSICAL),
    description(""), collectedBy(""), dateCollected(""),
    storageLocation(""), isProcessed(false) {}

// Parameterized constructor
Evidence::Evidence(int id, int caseID, EvidenceType t, const string& desc)
    : evidenceID(id), relatedCaseID(caseID), type(t),
    description(desc), collectedBy(""), dateCollected(getCurrentDateTime()),
    storageLocation("Evidence Locker"), isProcessed(false) {}

// Display evidence
void Evidence::display() const {
    cout << Colors::INFO << "  Evidence #" << evidenceID
        << Colors::RESET << " | Case #" << relatedCaseID << endl;
    cout << "    Type: " << evidenceTypeToString(type) << endl;
    cout << "    Description: " << description << endl;
    cout << "    Collected: " << dateCollected << " by "
        << (collectedBy.empty() ? "Unknown" : collectedBy) << endl;
    cout << "    Storage: " << storageLocation << endl;
    cout << "    Status: " << (isProcessed ? "Processed" : "Pending") << endl;
}

/*
================================================================================
                    INVESTIGATION ITEM IMPLEMENTATION
================================================================================
*/

// Default constructor
InvestigationItem::InvestigationItem()
    : caseID(0), caseTitle(""), status(InvestigationStatus::PENDING),
    assignedOfficer(""), dateQueued(""), priority(5) {}

// Parameterized constructor
InvestigationItem::InvestigationItem(int id, const string& title, const string& officer)
    : caseID(id), caseTitle(title), status(InvestigationStatus::PENDING),
    assignedOfficer(officer), dateQueued(getCurrentDateTime()), priority(5) {}

// Display investigation item
void InvestigationItem::display() const {
    cout << Colors::CYAN << "  Case #" << caseID << Colors::RESET
        << ": " << caseTitle << endl;
    cout << "    Status: " << statusToString(status) << endl;
    cout << "    Officer: " << assignedOfficer << endl;
    cout << "    Queued: " << dateQueued << endl;
    cout << "    Priority: " << priority << "/10" << endl;
}

/*
================================================================================
                    EXPRESSION EVALUATOR IMPLEMENTATION

    Uses Stack for expression evaluation algorithms
    Demonstrates classic stack applications
================================================================================
*/

// Constructor
ExpressionEvaluator::ExpressionEvaluator() {}

// Check if character is an operator
bool ExpressionEvaluator::isOperator(char c) const {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == '%');
}

// Get operator precedence
// Stack-based expression evaluation requires precedence handling
int ExpressionEvaluator::getPrecedence(char op) const {
    switch (op) {
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
    case '%':
        return 2;
    case '^':
        return 3;
    default:
        return 0;
    }
}

// Check if character is operand (digit)
bool ExpressionEvaluator::isOperand(char c) const {
    return (c >= '0' && c <= '9');
}

// Perform arithmetic operation
double ExpressionEvaluator::performOperation(double a, double b, char op) const {
    switch (op) {
    case '+': return a + b;
    case '-': return a - b;
    case '*': return a * b;
    case '/':
        if (b == 0) throw runtime_error("Division by zero");
        return a / b;
    case '%': return fmod(a, b);
    case '^': return pow(a, b);
    default:  return 0;
    }
}

// Convert infix to postfix using Shunting Yard algorithm
// Uses operator stack for conversion
// Complexity: O(n) where n is expression length
string ExpressionEvaluator::infixToPostfix(const string& infix) {
    LinkedStack<char> operatorStack;
    string postfix = "";

    for (int i = 0; i < static_cast<int>(infix.length()); i++) {
        char c = infix[i];

        // Skip whitespace
        if (c == ' ') continue;

        // If operand, add to output
        if (isOperand(c)) {
            // Handle multi-digit numbers
            while (i < infix.length() && (isOperand(infix[i]) || infix[i] == '.')) {
                postfix += infix[i];
                i++;
            }
            postfix += ' ';
            i--;
        }
        // If opening parenthesis, push to stack
        else if (c == '(') {
            operatorStack.push(c);
        }
        // If closing parenthesis, pop until opening found
        else if (c == ')') {
            while (!operatorStack.isEmpty() && operatorStack.peek() != '(') {
                postfix += operatorStack.pop();
                postfix += ' ';
            }
            if (!operatorStack.isEmpty()) {
                operatorStack.pop(); // Remove '('
            }
        }
        // If operator
        else if (isOperator(c)) {
            while (!operatorStack.isEmpty() &&
                operatorStack.peek() != '(' &&
                getPrecedence(operatorStack.peek()) >= getPrecedence(c)) {
                postfix += operatorStack.pop();
                postfix += ' ';
            }
            operatorStack.push(c);
        }
    }

    // Pop remaining operators
    while (!operatorStack.isEmpty()) {
        postfix += operatorStack.pop();
        postfix += ' ';
    }

    return postfix;
}

// Evaluate postfix expression
double ExpressionEvaluator::evaluatePostfix(const string& postfix) {
    LinkedStack<double> operandStack;

    for (int i = 0; i < static_cast<int>(postfix.length()); i++) {
        char c = postfix[i];

        // Skip whitespace
        if (c == ' ') continue;

        // If operand, parse number and push
        if (isOperand(c)) {
            double num = 0;
            while (i < postfix.length() && (isOperand(postfix[i]) || postfix[i] == '.')) {
                if (postfix[i] == '.') {
                    i++;
                    double decimal = 0.1;
                    while (i < postfix.length() && isOperand(postfix[i])) {
                        num += (postfix[i] - '0') * decimal;
                        decimal *= 0.1;
                        i++;
                    }
                    break;
                }
                num = num * 10 + (postfix[i] - '0');
                i++;
            }
            operandStack.push(num);
        }
        // If operator, pop two operands and compute
        else if (isOperator(c)) {
            if (operandStack.size() < 2) {
                throw runtime_error("Invalid postfix expression");
            }
            double b = operandStack.pop();
            double a = operandStack.pop();
            double result = performOperation(a, b, c);
            operandStack.push(result);
        }
    }

    if (operandStack.size() != 1) {
        throw runtime_error("Invalid postfix expression");
    }

    return operandStack.pop();
}

// Convert decimal to binary using stack
// Uses stack to store remainders (classic stack application)
// Complexity: O(log n) where n is the decimal number
string ExpressionEvaluator::decimalToBinary(int decimal) {
    if (decimal == 0) return "0";

    LinkedStack<int> remainderStack;
    bool isNegative = decimal < 0;
    decimal = abs(decimal);

    // Push remainders onto stack
    while (decimal > 0) {
        remainderStack.push(decimal % 2);
        decimal /= 2;
    }

    // Pop remainders to build binary string
    string binary = isNegative ? "-" : "";
    while (!remainderStack.isEmpty()) {
        binary += to_string(remainderStack.pop());
    }

    return binary;
}

// Full evaluation from infix expression
double ExpressionEvaluator::evaluateInfix(const string& infix) {
    string postfix = infixToPostfix(infix);
    return evaluatePostfix(postfix);
}

// Validate expression syntax
bool ExpressionEvaluator::validateExpression(const string& expr) const {
    int parentheses = 0;
    bool lastWasOperator = true;

    for (char c : expr) {
        if (c == ' ') continue;

        if (c == '(') {
            parentheses++;
            lastWasOperator = true;
        }
        else if (c == ')') {
            parentheses--;
            if (parentheses < 0) return false;
            lastWasOperator = false;
        }
        else if (isOperator(c)) {
            if (lastWasOperator && c != '-') return false;
            lastWasOperator = true;
        }
        else if (isOperand(c) || c == '.') {
            lastWasOperator = false;
        }
        else {
            return false;
        }
    }

    return parentheses == 0 && !lastWasOperator;
}

/*
================================================================================
                    SORTING ALGORITHMS IMPLEMENTATION

    Manual implementations - no STL sort used
    All algorithms operate on vector<CrimeRecord>
================================================================================
*/

// Insertion Sort Implementation
// Best for small arrays or nearly sorted data
// Complexity: O(n^2) average/worst, O(n) best (sorted)
void SortingAlgorithms::insertionSort(vector<CrimeRecord>& arr) {
    int n = static_cast<int>(arr.size());

    for (int i = 1; i < n; i++) {
        CrimeRecord key = arr[i];
        int j = i - 1;

        // Move elements greater than key one position ahead
        while (j >= 0 && arr[j].caseID > key.caseID) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// Quick Sort partition helper
// Chooses last element as pivot
int SortingAlgorithms::partition(vector<CrimeRecord>& arr, int low, int high) {
    int pivot = arr[high].caseID;
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j].caseID < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

// Quick Sort recursive helper
void SortingAlgorithms::quickSortHelper(vector<CrimeRecord>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSortHelper(arr, low, pi - 1);
        quickSortHelper(arr, pi + 1, high);
    }
}

// Quick Sort Implementation
// Efficient average case O(n log n)
// Complexity: O(n log n) average, O(n^2) worst
void SortingAlgorithms::quickSort(vector<CrimeRecord>& arr) {
    if (!arr.empty()) {
        quickSortHelper(arr, 0, arr.size() - 1);
    }
}

// Merge Sort merge helper
// Merges two sorted subarrays
void SortingAlgorithms::merge(vector<CrimeRecord>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Create temporary arrays
    vector<CrimeRecord> leftArr(n1);
    vector<CrimeRecord> rightArr(n2);

    // Copy data to temp arrays
    for (int i = 0; i < n1; i++)
        leftArr[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        rightArr[j] = arr[mid + 1 + j];

    // Merge temp arrays back
    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (leftArr[i].caseID <= rightArr[j].caseID) {
            arr[k] = leftArr[i];
            i++;
        }
        else {
            arr[k] = rightArr[j];
            j++;
        }
        k++;
    }

    // Copy remaining elements
    while (i < n1) {
        arr[k] = leftArr[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = rightArr[j];
        j++;
        k++;
    }
}

// Merge Sort recursive helper
void SortingAlgorithms::mergeSortHelper(vector<CrimeRecord>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSortHelper(arr, left, mid);
        mergeSortHelper(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

// Merge Sort Implementation
// Stable sort with guaranteed O(n log n)
// Complexity: O(n log n) all cases
void SortingAlgorithms::mergeSort(vector<CrimeRecord>& arr) {
    if (!arr.empty()) {
        mergeSortHelper(arr, 0, arr.size() - 1);
    }
}

// Sort by case ID with algorithm choice
void SortingAlgorithms::sortByCaseID(vector<CrimeRecord>& arr, const string& algorithm) {
    if (algorithm == "insertion") {
        insertionSort(arr);
    }
    else if (algorithm == "quick") {
        quickSort(arr);
    }
    else if (algorithm == "merge") {
        mergeSort(arr);
    }
}

// Sort by priority (using insertion sort for stability)
void SortingAlgorithms::sortByPriority(vector<CrimeRecord>& arr, const string& algorithm) {
    (void)algorithm; // Reserved for future use
    int n = static_cast<int>(arr.size());
    for (int i = 1; i < n; i++) {
        CrimeRecord key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j].priorityLevel < key.priorityLevel) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// Sort by date (using merge sort for stability)
void SortingAlgorithms::sortByDate(vector<CrimeRecord>& arr, const string& algorithm) {
    (void)algorithm; // Reserved for future use
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        CrimeRecord key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j].dateReported > key.dateReported) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

/*
================================================================================
                    SEARCHING ALGORITHMS IMPLEMENTATION
================================================================================
*/

// Linear Search Implementation
// Works on unsorted arrays
// Complexity: O(n)
int SearchingAlgorithms::linearSearch(const vector<CrimeRecord>& arr, int caseID) {
    for (int i = 0; i < static_cast<int>(arr.size()); i++) {
        if (arr[i].caseID == caseID) {
            return i;
        }
    }
    return -1; // Not found
}

// Binary Search Implementation
// Requires sorted array
// Complexity: O(log n)
int SearchingAlgorithms::binarySearch(const vector<CrimeRecord>& arr, int caseID) {
    int left = 0;
    int right = arr.size() - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (arr[mid].caseID == caseID) {
            return mid;
        }

        if (arr[mid].caseID < caseID) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }

    return -1; // Not found
}

// Search by crime type (returns all matches)
vector<CrimeRecord> SearchingAlgorithms::searchByCrimeType(const vector<CrimeRecord>& arr, CrimeType type) {
    vector<CrimeRecord> results;
    for (const auto& record : arr) {
        if (record.crimeType == type) {
            results.push_back(record);
        }
    }
    return results;
}

// Search by status
vector<CrimeRecord> SearchingAlgorithms::searchByStatus(const vector<CrimeRecord>& arr, InvestigationStatus status) {
    vector<CrimeRecord> results;
    for (const auto& record : arr) {
        if (record.status == status) {
            results.push_back(record);
        }
    }
    return results;
}

// Search by location (partial match)
vector<CrimeRecord> SearchingAlgorithms::searchByLocation(const vector<CrimeRecord>& arr, const string& location) {
    vector<CrimeRecord> results;
    for (const auto& record : arr) {
        if (record.location.find(location) != string::npos) {
            results.push_back(record);
        }
    }
    return results;
}

// Search by date range
vector<CrimeRecord> SearchingAlgorithms::searchByDateRange(const vector<CrimeRecord>& arr,
    const string& startDate, const string& endDate) {
    vector<CrimeRecord> results;
    for (const auto& record : arr) {
        if (record.dateReported >= startDate && record.dateReported <= endDate) {
            results.push_back(record);
        }
    }
    return results;
}

/*
================================================================================
                    CRIME STATISTICS IMPLEMENTATION
================================================================================
*/

// Constructor
CrimeStatistics::CrimeStatistics() {
    reset();
}

// Reset all values
void CrimeStatistics::reset() {
    totalCrimes = 0;
    pendingCases = 0;
    inProgressCases = 0;
    closedCases = 0;
    coldCases = 0;

    theftCount = 0;
    assaultCount = 0;
    burglaryCount = 0;
    fraudCount = 0;
    vandalismCount = 0;
    robberyCount = 0;
    homicideCount = 0;
    kidnappingCount = 0;
    cybercrimeCount = 0;
    drugOffenseCount = 0;
    arsonCount = 0;
    otherCount = 0;

    highPriority = 0;
    mediumPriority = 0;
    lowPriority = 0;
}

// Display statistics
void CrimeStatistics::display() const {
    cout << Colors::HEADER << "\n========================================" << endl;
    cout << "         CRIME STATISTICS REPORT        " << endl;
    cout << "========================================" << Colors::RESET << endl;

    cout << Colors::SUBHEADER << "\n--- General Overview ---" << Colors::RESET << endl;
    cout << "  Total Crimes:      " << totalCrimes << endl;
    cout << "  Pending Cases:     " << pendingCases << endl;
    cout << "  In Progress:       " << inProgressCases << endl;
    cout << "  Closed Cases:      " << closedCases << endl;
    cout << "  Cold Cases:        " << coldCases << endl;

    cout << Colors::SUBHEADER << "\n--- Crime Type Distribution ---" << Colors::RESET << endl;
    cout << "  Theft:             " << theftCount << endl;
    cout << "  Assault:           " << assaultCount << endl;
    cout << "  Burglary:          " << burglaryCount << endl;
    cout << "  Fraud:             " << fraudCount << endl;
    cout << "  Vandalism:         " << vandalismCount << endl;
    cout << "  Robbery:           " << robberyCount << endl;
    cout << "  Homicide:          " << homicideCount << endl;
    cout << "  Kidnapping:        " << kidnappingCount << endl;
    cout << "  Cybercrime:        " << cybercrimeCount << endl;
    cout << "  Drug Offense:      " << drugOffenseCount << endl;
    cout << "  Arson:             " << arsonCount << endl;
    cout << "  Other:             " << otherCount << endl;

    cout << Colors::SUBHEADER << "\n--- Priority Distribution ---" << Colors::RESET << endl;
    cout << "  High (8-10):       " << highPriority << endl;
    cout << "  Medium (4-7):      " << mediumPriority << endl;
    cout << "  Low (1-3):         " << lowPriority << endl;

    cout << Colors::BORDER << "\n========================================" << Colors::RESET << endl;
}

/*
================================================================================
                    REPORTING MODULE IMPLEMENTATION
================================================================================
*/

// Helper for bar chart display
void ReportingModule::printBar(int count, int maxCount, int barWidth) {
    int filled = (maxCount > 0) ? (count * barWidth / maxCount) : 0;
    cout << "[";
    for (int i = 0; i < barWidth; i++) {
        cout << (i < filled ? "#" : " ");
    }
    cout << "] " << count;
}

// Generate statistics from crime records
CrimeStatistics ReportingModule::generateStatistics(const vector<CrimeRecord>& records) {
    CrimeStatistics stats;
    stats.totalCrimes = records.size();

    for (const auto& record : records) {
        // Count by status
        switch (record.status) {
        case InvestigationStatus::PENDING:
            stats.pendingCases++;
            break;
        case InvestigationStatus::IN_PROGRESS:
        case InvestigationStatus::UNDER_REVIEW:
            stats.inProgressCases++;
            break;
        case InvestigationStatus::CLOSED:
            stats.closedCases++;
            break;
        case InvestigationStatus::COLD_CASE:
            stats.coldCases++;
            break;
        }

        // Count by crime type
        switch (record.crimeType) {
        case CrimeType::THEFT:        stats.theftCount++; break;
        case CrimeType::ASSAULT:      stats.assaultCount++; break;
        case CrimeType::BURGLARY:     stats.burglaryCount++; break;
        case CrimeType::FRAUD:        stats.fraudCount++; break;
        case CrimeType::VANDALISM:    stats.vandalismCount++; break;
        case CrimeType::ROBBERY:      stats.robberyCount++; break;
        case CrimeType::HOMICIDE:     stats.homicideCount++; break;
        case CrimeType::KIDNAPPING:   stats.kidnappingCount++; break;
        case CrimeType::CYBERCRIME:   stats.cybercrimeCount++; break;
        case CrimeType::DRUG_OFFENSE: stats.drugOffenseCount++; break;
        case CrimeType::ARSON:        stats.arsonCount++; break;
        case CrimeType::OTHER:        stats.otherCount++; break;
        }

        // Count by priority
        if (record.priorityLevel >= 8) {
            stats.highPriority++;
        }
        else if (record.priorityLevel >= 4) {
            stats.mediumPriority++;
        }
        else {
            stats.lowPriority++;
        }
    }

    return stats;
}

// Display all records in formatted table
void ReportingModule::displayAllRecords(const vector<CrimeRecord>& records) {
    cout << Colors::HEADER << "\n=============================================" << endl;
    cout << "            ALL CRIME RECORDS                " << endl;
    cout << "=============================================" << Colors::RESET << endl;

    if (records.empty()) {
        cout << Colors::WARNING << "  No records to display." << Colors::RESET << endl;
        return;
    }

    cout << Colors::SUBHEADER << left << setw(8) << "CaseID"
        << setw(25) << "Title" << setw(12) << "Type"
        << setw(12) << "Status" << setw(8) << "Priority" << Colors::RESET << endl;
    cout << Colors::BORDER << string(65, '-') << Colors::RESET << endl;

    for (const auto& record : records) {
        cout << left << setw(8) << record.caseID
            << setw(25) << record.crimeTitle.substr(0, 23)
            << setw(12) << crimeTypeToString(record.crimeType).substr(0, 10)
            << setw(12) << statusToString(record.status).substr(0, 10)
            << setw(8) << record.priorityLevel << endl;
    }

    cout << Colors::BORDER << string(65, '-') << Colors::RESET << endl;
    cout << "  Total: " << records.size() << " records" << endl;
}

// Display records by crime type
void ReportingModule::displayByCrimeType(const vector<CrimeRecord>& records) {
    cout << Colors::HEADER << "\n=== Records by Crime Type ===" << Colors::RESET << endl;

    for (int i = 0; i <= 11; i++) {
        CrimeType type = static_cast<CrimeType>(i);
        vector<CrimeRecord> filtered = SearchingAlgorithms::searchByCrimeType(records, type);

        if (!filtered.empty()) {
            cout << Colors::SUBHEADER << "\n" << crimeTypeToString(type)
                << " (" << filtered.size() << " cases)" << Colors::RESET << endl;
            for (const auto& record : filtered) {
                cout << "  - Case #" << record.caseID << ": " << record.crimeTitle << endl;
            }
        }
    }
}

// Display records by status
void ReportingModule::displayByStatus(const vector<CrimeRecord>& records) {
    cout << Colors::HEADER << "\n=== Records by Status ===" << Colors::RESET << endl;

    InvestigationStatus statuses[] = {
        InvestigationStatus::PENDING,
        InvestigationStatus::IN_PROGRESS,
        InvestigationStatus::UNDER_REVIEW,
        InvestigationStatus::CLOSED,
        InvestigationStatus::COLD_CASE
    };

    for (auto status : statuses) {
        vector<CrimeRecord> filtered = SearchingAlgorithms::searchByStatus(records, status);

        if (!filtered.empty()) {
            cout << Colors::SUBHEADER << "\n" << statusToString(status)
                << " (" << filtered.size() << " cases)" << Colors::RESET << endl;
            for (const auto& record : filtered) {
                cout << "  - Case #" << record.caseID << ": " << record.crimeTitle << endl;
            }
        }
    }
}

// Display priority distribution chart
void ReportingModule::displayPriorityChart(const CrimeStatistics& stats) {
    cout << Colors::HEADER << "\n=== Priority Distribution ===" << Colors::RESET << endl;

    int maxCount = max({ stats.highPriority, stats.mediumPriority, stats.lowPriority });

    cout << Colors::RED << "  High (8-10):   ";
    printBar(stats.highPriority, maxCount, 30);
    cout << Colors::RESET << endl;

    cout << Colors::YELLOW << "  Medium (4-7):  ";
    printBar(stats.mediumPriority, maxCount, 30);
    cout << Colors::RESET << endl;

    cout << Colors::GREEN << "  Low (1-3):     ";
    printBar(stats.lowPriority, maxCount, 30);
    cout << Colors::RESET << endl;
}

// Display crime type distribution chart
void ReportingModule::displayCrimeTypeChart(const CrimeStatistics& stats) {
    cout << Colors::HEADER << "\n=== Crime Type Distribution ===" << Colors::RESET << endl;

    int maxCount = max({ stats.theftCount, stats.assaultCount, stats.burglaryCount,
                       stats.fraudCount, stats.vandalismCount, stats.robberyCount,
                       stats.homicideCount, stats.kidnappingCount, stats.cybercrimeCount,
                       stats.drugOffenseCount, stats.arsonCount, stats.otherCount });

    cout << "  Theft:         "; printBar(stats.theftCount, maxCount, 25); cout << endl;
    cout << "  Assault:       "; printBar(stats.assaultCount, maxCount, 25); cout << endl;
    cout << "  Burglary:      "; printBar(stats.burglaryCount, maxCount, 25); cout << endl;
    cout << "  Fraud:         "; printBar(stats.fraudCount, maxCount, 25); cout << endl;
    cout << "  Vandalism:     "; printBar(stats.vandalismCount, maxCount, 25); cout << endl;
    cout << "  Robbery:       "; printBar(stats.robberyCount, maxCount, 25); cout << endl;
    cout << "  Homicide:      "; printBar(stats.homicideCount, maxCount, 25); cout << endl;
    cout << "  Kidnapping:    "; printBar(stats.kidnappingCount, maxCount, 25); cout << endl;
    cout << "  Cybercrime:    "; printBar(stats.cybercrimeCount, maxCount, 25); cout << endl;
    cout << "  Drug Offense:  "; printBar(stats.drugOffenseCount, maxCount, 25); cout << endl;
    cout << "  Arson:         "; printBar(stats.arsonCount, maxCount, 25); cout << endl;
    cout << "  Other:         "; printBar(stats.otherCount, maxCount, 25); cout << endl;
}

// Generate text report
string ReportingModule::generateTextReport(const vector<CrimeRecord>& records,
    const CrimeStatistics& stats) {
    stringstream report;

    report << "========================================\n";
    report << "     CRIME RECORD SYSTEM REPORT\n";
    report << "     Generated: " << getCurrentDateTime() << "\n";
    report << "========================================\n\n";

    report << "SUMMARY\n";
    report << "-------\n";
    report << "Total Crimes: " << stats.totalCrimes << "\n";
    report << "Pending: " << stats.pendingCases << "\n";
    report << "In Progress: " << stats.inProgressCases << "\n";
    report << "Closed: " << stats.closedCases << "\n";
    report << "Cold Cases: " << stats.coldCases << "\n\n";

    report << "PRIORITY BREAKDOWN\n";
    report << "-----------------\n";
    report << "High Priority: " << stats.highPriority << "\n";
    report << "Medium Priority: " << stats.mediumPriority << "\n";
    report << "Low Priority: " << stats.lowPriority << "\n\n";

    report << "CASE DETAILS\n";
    report << "------------\n";
    for (const auto& record : records) {
        report << "Case #" << record.caseID << ": " << record.crimeTitle << "\n";
        report << "  Type: " << crimeTypeToString(record.crimeType) << "\n";
        report << "  Status: " << statusToString(record.status) << "\n";
        report << "  Priority: " << record.priorityLevel << "/10\n\n";
    }

    return report.str();
}

// Compare search algorithms performance
void ReportingModule::compareSearchAlgorithms(const vector<CrimeRecord>& records, int searchKey) {
    cout << Colors::HEADER << "\n=== Search Algorithm Comparison ===" << Colors::RESET << endl;

    if (records.empty()) {
        cout << Colors::WARNING << "  No records to search." << Colors::RESET << endl;
        return;
    }

    // Linear Search
    clock_t start = clock();
    int linearResult = SearchingAlgorithms::linearSearch(records, searchKey);
    clock_t end = clock();
    double linearTime = double(end - start) / CLOCKS_PER_SEC * 1000;

    // Create sorted copy for binary search
    vector<CrimeRecord> sortedRecords = records;
    SortingAlgorithms::quickSort(sortedRecords);

    // Binary Search
    start = clock();
    int binaryResult = SearchingAlgorithms::binarySearch(sortedRecords, searchKey);
    end = clock();
    double binaryTime = double(end - start) / CLOCKS_PER_SEC * 1000;

    cout << Colors::INFO << "\n  Searching for Case ID: " << searchKey << Colors::RESET << endl;
    cout << Colors::BORDER << string(50, '-') << Colors::RESET << endl;

    cout << "  Linear Search:" << endl;
    cout << "    Result: " << (linearResult >= 0 ? "Found at index " + to_string(linearResult) : "Not found") << endl;
    cout << "    Time: " << fixed << setprecision(6) << linearTime << " ms" << endl;
    cout << "    Complexity: O(n)" << endl;

    cout << "\n  Binary Search:" << endl;
    cout << "    Result: " << (binaryResult >= 0 ? "Found at index " + to_string(binaryResult) : "Not found") << endl;
    cout << "    Time: " << fixed << setprecision(6) << binaryTime << " ms" << endl;
    cout << "    Complexity: O(log n)" << endl;
    cout << "    Note: Requires sorted array" << endl;

    cout << Colors::BORDER << string(50, '-') << Colors::RESET << endl;
}

// Compare sorting algorithms performance
void ReportingModule::compareSortingAlgorithms(vector<CrimeRecord> records) {
    cout << Colors::HEADER << "\n=== Sorting Algorithm Comparison ===" << Colors::RESET << endl;

    if (records.empty()) {
        cout << Colors::WARNING << "  No records to sort." << Colors::RESET << endl;
        return;
    }

    int n = records.size();
    cout << Colors::INFO << "\n  Sorting " << n << " records" << Colors::RESET << endl;
    cout << Colors::BORDER << string(50, '-') << Colors::RESET << endl;

    // Insertion Sort
    vector<CrimeRecord> insertionArr = records;
    clock_t start = clock();
    SortingAlgorithms::insertionSort(insertionArr);
    clock_t end = clock();
    double insertionTime = double(end - start) / CLOCKS_PER_SEC * 1000;

    // Quick Sort
    vector<CrimeRecord> quickArr = records;
    start = clock();
    SortingAlgorithms::quickSort(quickArr);
    end = clock();
    double quickTime = double(end - start) / CLOCKS_PER_SEC * 1000;

    // Merge Sort
    vector<CrimeRecord> mergeArr = records;
    start = clock();
    SortingAlgorithms::mergeSort(mergeArr);
    end = clock();
    double mergeTime = double(end - start) / CLOCKS_PER_SEC * 1000;

    cout << "  Insertion Sort:" << endl;
    cout << "    Time: " << fixed << setprecision(6) << insertionTime << " ms" << endl;
    cout << "    Complexity: O(n^2) average, O(n) best" << endl;
    cout << "    Stable: Yes" << endl;

    cout << "\n  Quick Sort:" << endl;
    cout << "    Time: " << fixed << setprecision(6) << quickTime << " ms" << endl;
    cout << "    Complexity: O(n log n) average, O(n^2) worst" << endl;
    cout << "    Stable: No" << endl;

    cout << "\n  Merge Sort:" << endl;
    cout << "    Time: " << fixed << setprecision(6) << mergeTime << " ms" << endl;
    cout << "    Complexity: O(n log n) all cases" << endl;
    cout << "    Stable: Yes" << endl;

    cout << Colors::BORDER << string(50, '-') << Colors::RESET << endl;
}

/*
================================================================================
                    ALGORITHM ANALYSIS IMPLEMENTATION
================================================================================
*/

// Display AVL Tree complexity analysis
void AlgorithmAnalysis::displayAVLComplexity() {
    cout << Colors::HEADER << "\n=== AVL TREE COMPLEXITY ANALYSIS ===" << Colors::RESET << endl;
    cout << Colors::BORDER << string(60, '-') << Colors::RESET << endl;

    cout << Colors::SUBHEADER << "\nOperation      | Average  | Worst    | Space" << Colors::RESET << endl;
    cout << Colors::BORDER << string(60, '-') << Colors::RESET << endl;
    cout << "Insert         | O(log n) | O(log n) | O(1)" << endl;
    cout << "Delete         | O(log n) | O(log n) | O(1)" << endl;
    cout << "Search         | O(log n) | O(log n) | O(1)" << endl;
    cout << "Traversal      | O(n)     | O(n)     | O(n) for result" << endl;
    cout << "Get Height     | O(1)     | O(1)     | O(1)" << endl;
    cout << "Rotation       | O(1)     | O(1)     | O(1)" << endl;

    cout << Colors::INFO << "\nWhy AVL Tree?" << Colors::RESET << endl;
    cout << "  - Guarantees O(log n) worst case (unlike BST)" << endl;
    cout << "  - Self-balancing via rotations" << endl;
    cout << "  - Maintains sorted order (unlike hash table)" << endl;
    cout << "  - Balance factor always -1, 0, or 1" << endl;

    cout << Colors::WARNING << "\nRotation Cases:" << Colors::RESET << endl;
    cout << "  - LL (Left-Left): Right rotation" << endl;
    cout << "  - RR (Right-Right): Left rotation" << endl;
    cout << "  - LR (Left-Right): Left then Right rotation" << endl;
    cout << "  - RL (Right-Left): Right then Left rotation" << endl;
}

// Display Queue complexity analysis
void AlgorithmAnalysis::displayQueueComplexity() {
    cout << Colors::HEADER << "\n=== QUEUE COMPLEXITY ANALYSIS ===" << Colors::RESET << endl;
    cout << Colors::BORDER << string(60, '-') << Colors::RESET << endl;

    cout << Colors::SUBHEADER << "\nOperation      | Time     | Space    | Notes" << Colors::RESET << endl;
    cout << Colors::BORDER << string(60, '-') << Colors::RESET << endl;
    cout << "Enqueue        | O(1)     | O(1)     | Add to rear" << endl;
    cout << "Dequeue        | O(1)     | O(1)     | Remove from front" << endl;
    cout << "Peek           | O(1)     | O(1)     | View front" << endl;
    cout << "isEmpty        | O(1)     | O(1)     | Check empty" << endl;
    cout << "Size           | O(1)     | O(1)     | Counter maintained" << endl;

    cout << Colors::INFO << "\nLinked Queue vs Circular Queue:" << Colors::RESET << endl;
    cout << "  Linked Queue:" << endl;
    cout << "    - Dynamic size (no capacity limit)" << endl;
    cout << "    - Uses more memory per element (pointer overhead)" << endl;
    cout << "    - Good for unpredictable queue sizes" << endl;
    cout << "  Circular Queue:" << endl;
    cout << "    - Fixed capacity" << endl;
    cout << "    - More memory efficient" << endl;
    cout << "    - Better cache locality" << endl;

    cout << Colors::WARNING << "\nQueue preserves FIFO fairness for workflow" << Colors::RESET << endl;
}

// Display Stack complexity analysis
void AlgorithmAnalysis::displayStackComplexity() {
    cout << Colors::HEADER << "\n=== STACK COMPLEXITY ANALYSIS ===" << Colors::RESET << endl;
    cout << Colors::BORDER << string(60, '-') << Colors::RESET << endl;

    cout << Colors::SUBHEADER << "\nOperation      | Time     | Space    | Notes" << Colors::RESET << endl;
    cout << Colors::BORDER << string(60, '-') << Colors::RESET << endl;
    cout << "Push           | O(1)     | O(1)     | Add to top" << endl;
    cout << "Pop            | O(1)     | O(1)     | Remove from top" << endl;
    cout << "Peek           | O(1)     | O(1)     | View top" << endl;
    cout << "isEmpty        | O(1)     | O(1)     | Check empty" << endl;
    cout << "Size           | O(1)     | O(1)     | Counter maintained" << endl;

    cout << Colors::INFO << "\nStack Applications in This System:" << Colors::RESET << endl;
    cout << "  1. Evidence Processing (LIFO order)" << endl;
    cout << "  2. Infix to Postfix conversion" << endl;
    cout << "  3. Postfix expression evaluation" << endl;
    cout << "  4. Decimal to Binary conversion" << endl;

    cout << Colors::WARNING << "\nStack enables backtracking and undo operations" << Colors::RESET << endl;
}

// Display Sorting algorithms complexity
void AlgorithmAnalysis::displaySortingComplexity() {
    cout << Colors::HEADER << "\n=== SORTING ALGORITHMS COMPLEXITY ===" << Colors::RESET << endl;
    cout << Colors::BORDER << string(70, '-') << Colors::RESET << endl;

    cout << Colors::SUBHEADER << "\nAlgorithm       | Best     | Average  | Worst    | Space | Stable" << Colors::RESET << endl;
    cout << Colors::BORDER << string(70, '-') << Colors::RESET << endl;
    cout << "Insertion Sort  | O(n)     | O(n^2)   | O(n^2)   | O(1)  | Yes" << endl;
    cout << "Quick Sort      | O(nlogn) | O(nlogn) | O(n^2)   | O(logn)| No" << endl;
    cout << "Merge Sort      | O(nlogn) | O(nlogn) | O(nlogn) | O(n)  | Yes" << endl;

    cout << Colors::INFO << "\nWhen to Use Each:" << Colors::RESET << endl;
    cout << "  Insertion Sort:" << endl;
    cout << "    - Small arrays (n < 50)" << endl;
    cout << "    - Nearly sorted data" << endl;
    cout << "    - Online sorting (streaming data)" << endl;
    cout << "  Quick Sort:" << endl;
    cout << "    - Large arrays" << endl;
    cout << "    - When average case matters more than worst" << endl;
    cout << "    - In-place sorting needed" << endl;
    cout << "  Merge Sort:" << endl;
    cout << "    - Stability required" << endl;
    cout << "    - Guaranteed O(n log n) needed" << endl;
    cout << "    - External sorting (large files)" << endl;
}

// Display Searching algorithms complexity
void AlgorithmAnalysis::displaySearchingComplexity() {
    cout << Colors::HEADER << "\n=== SEARCHING ALGORITHMS COMPLEXITY ===" << Colors::RESET << endl;
    cout << Colors::BORDER << string(60, '-') << Colors::RESET << endl;

    cout << Colors::SUBHEADER << "\nAlgorithm       | Best     | Average  | Worst    | Requires" << Colors::RESET << endl;
    cout << Colors::BORDER << string(60, '-') << Colors::RESET << endl;
    cout << "Linear Search   | O(1)     | O(n)     | O(n)     | Nothing" << endl;
    cout << "Binary Search   | O(1)     | O(log n) | O(log n) | Sorted array" << endl;
    cout << "AVL Search      | O(1)     | O(log n) | O(log n) | AVL Tree" << endl;

    cout << Colors::INFO << "\nComparison:" << Colors::RESET << endl;
    cout << "  Linear Search:" << endl;
    cout << "    + Works on unsorted data" << endl;
    cout << "    + Simple implementation" << endl;
    cout << "    - Slow for large datasets" << endl;
    cout << "  Binary Search:" << endl;
    cout << "    + Very fast" << endl;
    cout << "    - Requires sorted data" << endl;
    cout << "    - Sorting has overhead" << endl;
    cout << "  AVL Search:" << endl;
    cout << "    + Fast and maintains order" << endl;
    cout << "    + No separate sorting needed" << endl;
    cout << "    - More complex structure" << endl;
}

// Display complete analysis
void AlgorithmAnalysis::displayFullAnalysis() {
    displayAVLComplexity();
    cout << endl;
    displayQueueComplexity();
    cout << endl;
    displayStackComplexity();
    cout << endl;
    displaySortingComplexity();
    cout << endl;
    displaySearchingComplexity();
}

// Display comparison table
void AlgorithmAnalysis::displayComparisonTable() {
    cout << Colors::HEADER << "\n=== DATA STRUCTURE COMPARISON ===" << Colors::RESET << endl;
    cout << Colors::BORDER << string(70, '-') << Colors::RESET << endl;

    cout << Colors::SUBHEADER << "\nDS              | Insert   | Delete   | Search   | Order  | Use Case" << Colors::RESET << endl;
    cout << Colors::BORDER << string(70, '-') << Colors::RESET << endl;
    cout << "AVL Tree        | O(log n) | O(log n) | O(log n) | Yes    | Primary storage" << endl;
    cout << "Queue           | O(1)     | O(1)     | O(n)     | FIFO   | Workflow" << endl;
    cout << "Stack           | O(1)     | O(1)     | O(n)     | LIFO   | Evidence/Eval" << endl;
    cout << "Array/Vector    | O(n)     | O(n)     | O(n)     | Index  | Reports" << endl;

    cout << Colors::BORDER << string(70, '-') << Colors::RESET << endl;
}

// Display design decisions
void AlgorithmAnalysis::displayDesignDecisions() {
    cout << Colors::HEADER << "\n=== DESIGN DECISIONS & JUSTIFICATION ===" << Colors::RESET << endl;
    cout << Colors::BORDER << string(60, '-') << Colors::RESET << endl;

    cout << Colors::SUBHEADER << "\n1. AVL Tree for Crime Records" << Colors::RESET << endl;
    cout << "   Chosen because:" << endl;
    cout << "     - Guarantees O(log n) for all operations" << endl;
    cout << "     - Maintains sorted order by Case ID" << endl;
    cout << "     - Supports range queries" << endl;
    cout << "   Alternatives rejected:" << endl;
    cout << "     - BST: Can become O(n) if skewed" << endl;
    cout << "     - Hash Table: No ordering, no range queries" << endl;
    cout << "     - Array: O(n) insertion/deletion" << endl;

    cout << Colors::SUBHEADER << "\n2. Queue for Investigation Workflow" << Colors::RESET << endl;
    cout << "   Chosen because:" << endl;
    cout << "     - FIFO ensures fair processing order" << endl;
    cout << "     - O(1) operations" << endl;
    cout << "     - Models real-world workflow" << endl;
    cout << "   Alternatives rejected:" << endl;
    cout << "     - Stack: LIFO would be unfair" << endl;
    cout << "     - Priority Queue: May bias against older cases" << endl;

    cout << Colors::SUBHEADER << "\n3. Stack for Evidence Handling" << Colors::RESET << endl;
    cout << "   Chosen because:" << endl;
    cout << "     - LIFO suits evidence processing" << endl;
    cout << "     - Classic data structure for expression eval" << endl;
    cout << "     - Supports backtracking/undo" << endl;
    cout << "   Alternatives rejected:" << endl;
    cout << "     - Queue: Wrong order for evidence" << endl;

    cout << Colors::SUBHEADER << "\n4. Vector for Reports (Dynamic Array)" << Colors::RESET << endl;
    cout << "   Chosen because:" << endl;
    cout << "     - Stores traversal snapshots" << endl;
    cout << "     - Dynamic sizing for varying report sizes" << endl;
    cout << "     - Sorting algorithms work on arrays" << endl;
    cout << "   Note: Not used as primary DS, only for output" << endl;

    cout << Colors::SUBHEADER << "\n5. Templates for Type Generalization" << Colors::RESET << endl;
    cout << "   Used for:" << endl;
    cout << "     - AVL Tree nodes and operations" << endl;
    cout << "     - Queue and Stack implementations" << endl;
    cout << "   Purpose:" << endl;
    cout << "     - Reusability with different data types" << endl;
    cout << "     - Type safety at compile time" << endl;
    cout << "   Note: DSA logic remains visible and manual" << endl;

    cout << Colors::BORDER << string(60, '-') << Colors::RESET << endl;
}

/*
================================================================================
                    UI MODULE IMPLEMENTATION
================================================================================
*/

// Clear screen (cross-platform)
void UIModule::clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Wait for user input
void UIModule::waitForEnter() {
    cout << Colors::INPUT_PROMPT << "\n  Press Enter to continue..." << Colors::RESET;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

// Print horizontal line
void UIModule::printLine(char c, int width) {
    cout << Colors::BORDER << string(width, c) << Colors::RESET << endl;
}

// Print centered text
void UIModule::printCentered(const string& text, int width) {
    int padding = (width - text.length()) / 2;
    cout << string(padding, ' ') << text << endl;
}

// Print header box
void UIModule::printHeader(const string& title) {
    int width = 60;
    cout << Colors::HEADER << endl;
    cout << "  " << string(width, '=') << endl;
    cout << "  ";
    printCentered(title, width);
    cout << "  " << string(width, '=') << endl;
    cout << Colors::RESET << endl;
}

// Validate integer input
bool UIModule::getIntInput(int& value, const string& prompt, int min, int max) {
    cout << Colors::INPUT_PROMPT << "  " << prompt << Colors::RESET;

    if (!(cin >> value)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        displayError("Invalid input. Please enter a number.");
        return false;
    }

    if (value < min || value > max) {
        displayError("Value must be between " + to_string(min) + " and " + to_string(max));
        return false;
    }

    return true;
}

// Validate string input
bool UIModule::getStringInput(string& value, const string& prompt, bool allowEmpty) {
    cout << Colors::INPUT_PROMPT << "  " << prompt << Colors::RESET;
    cin.ignore();
    getline(cin, value);

    if (!allowEmpty && value.empty()) {
        displayError("Input cannot be empty.");
        return false;
    }

    return true;
}

// Display main menu
void UIModule::displayMainMenu() {
    cout << Colors::HEADER << endl;
    cout << "  ============================================================" << endl;
    cout << "      CRIME RECORD INDEXING & INVESTIGATION WORKFLOW SYSTEM    " << endl;
    cout << "                        (CRIW SYSTEM)                          " << endl;
    cout << "  ============================================================" << endl;
    cout << Colors::RESET << endl;

    cout << Colors::MENU_ITEM << "  [1]" << Colors::RESET << " Crime Record Management" << endl;
    cout << Colors::MENU_ITEM << "  [2]" << Colors::RESET << " Investigation Queue" << endl;
    cout << Colors::MENU_ITEM << "  [3]" << Colors::RESET << " Evidence Handling" << endl;
    cout << Colors::MENU_ITEM << "  [4]" << Colors::RESET << " Reports & Statistics" << endl;
    cout << Colors::MENU_ITEM << "  [5]" << Colors::RESET << " Algorithm Analysis" << endl;
    cout << Colors::MENU_ITEM << "  [6]" << Colors::RESET << " Add Sample Data" << endl;
    cout << Colors::MENU_ITEM << "  [0]" << Colors::RESET << " Exit System" << endl;

    printLine('-', 60);
}

// Display crime record submenu
void UIModule::displayCrimeRecordMenu() {
    printHeader("CRIME RECORD MANAGEMENT");

    cout << Colors::MENU_ITEM << "  [1]" << Colors::RESET << " Register New Crime" << endl;
    cout << Colors::MENU_ITEM << "  [2]" << Colors::RESET << " Search Crime by ID" << endl;
    cout << Colors::MENU_ITEM << "  [3]" << Colors::RESET << " Update Crime Record" << endl;
    cout << Colors::MENU_ITEM << "  [4]" << Colors::RESET << " Delete Crime Record" << endl;
    cout << Colors::MENU_ITEM << "  [5]" << Colors::RESET << " View All Crimes" << endl;
    cout << Colors::MENU_ITEM << "  [6]" << Colors::RESET << " View by Traversal Order" << endl;
    cout << Colors::MENU_ITEM << "  [7]" << Colors::RESET << " Display AVL Tree Structure" << endl;
    cout << Colors::MENU_ITEM << "  [0]" << Colors::RESET << " Back to Main Menu" << endl;

    printLine('-', 60);
}

// Display investigation submenu
void UIModule::displayInvestigationMenu() {
    printHeader("INVESTIGATION WORKFLOW");

    cout << Colors::MENU_ITEM << "  [1]" << Colors::RESET << " Add Case to Queue" << endl;
    cout << Colors::MENU_ITEM << "  [2]" << Colors::RESET << " Process Next Case" << endl;
    cout << Colors::MENU_ITEM << "  [3]" << Colors::RESET << " View Queue Status" << endl;
    cout << Colors::MENU_ITEM << "  [4]" << Colors::RESET << " View All Queued Cases" << endl;
    cout << Colors::MENU_ITEM << "  [0]" << Colors::RESET << " Back to Main Menu" << endl;

    printLine('-', 60);
}

// Display evidence submenu
void UIModule::displayEvidenceMenu() {
    printHeader("EVIDENCE HANDLING");

    cout << Colors::MENU_ITEM << "  [1]" << Colors::RESET << " Add Evidence" << endl;
    cout << Colors::MENU_ITEM << "  [2]" << Colors::RESET << " Process Latest Evidence" << endl;
    cout << Colors::MENU_ITEM << "  [3]" << Colors::RESET << " View Evidence Stack" << endl;
    cout << Colors::MENU_ITEM << "  [4]" << Colors::RESET << " Expression Calculator" << endl;
    cout << Colors::MENU_ITEM << "  [5]" << Colors::RESET << " Decimal to Binary Converter" << endl;
    cout << Colors::MENU_ITEM << "  [0]" << Colors::RESET << " Back to Main Menu" << endl;

    printLine('-', 60);
}

// Display reporting submenu
void UIModule::displayReportingMenu() {
    printHeader("REPORTS & STATISTICS");

    cout << Colors::MENU_ITEM << "  [1]" << Colors::RESET << " Generate Full Statistics" << endl;
    cout << Colors::MENU_ITEM << "  [2]" << Colors::RESET << " View Priority Chart" << endl;
    cout << Colors::MENU_ITEM << "  [3]" << Colors::RESET << " View Crime Type Chart" << endl;
    cout << Colors::MENU_ITEM << "  [4]" << Colors::RESET << " Search by Criteria" << endl;
    cout << Colors::MENU_ITEM << "  [5]" << Colors::RESET << " Sort and Display Records" << endl;
    cout << Colors::MENU_ITEM << "  [6]" << Colors::RESET << " Compare Search Algorithms" << endl;
    cout << Colors::MENU_ITEM << "  [7]" << Colors::RESET << " Compare Sorting Algorithms" << endl;
    cout << Colors::MENU_ITEM << "  [0]" << Colors::RESET << " Back to Main Menu" << endl;

    printLine('-', 60);
}

// Display algorithm analysis submenu
void UIModule::displayAlgorithmMenu() {
    printHeader("ALGORITHM ANALYSIS");

    cout << Colors::MENU_ITEM << "  [1]" << Colors::RESET << " AVL Tree Complexity" << endl;
    cout << Colors::MENU_ITEM << "  [2]" << Colors::RESET << " Queue Complexity" << endl;
    cout << Colors::MENU_ITEM << "  [3]" << Colors::RESET << " Stack Complexity" << endl;
    cout << Colors::MENU_ITEM << "  [4]" << Colors::RESET << " Sorting Algorithms" << endl;
    cout << Colors::MENU_ITEM << "  [5]" << Colors::RESET << " Searching Algorithms" << endl;
    cout << Colors::MENU_ITEM << "  [6]" << Colors::RESET << " Complete Analysis" << endl;
    cout << Colors::MENU_ITEM << "  [7]" << Colors::RESET << " DS Comparison Table" << endl;
    cout << Colors::MENU_ITEM << "  [8]" << Colors::RESET << " Design Decisions" << endl;
    cout << Colors::MENU_ITEM << "  [0]" << Colors::RESET << " Back to Main Menu" << endl;

    printLine('-', 60);
}

// Display welcome screen
void UIModule::displayWelcome() {
    clearScreen();
    cout << Colors::HEADER << endl;
    cout << "  ================================================================" << endl;
    cout << "                                                                  " << endl;
    cout << "     Crime Record Indexing & Investigation Workflow System        " << endl;
    cout << "                                                                  " << endl;
    cout << "  ================================================================" << endl;
    cout << Colors::RESET << endl;

    cout << Colors::INFO << "  Data Structures Used:" << Colors::RESET << endl;
    cout << "    - AVL Tree for Crime Record Storage (O(log n) operations)" << endl;
    cout << "    - Queue for Investigation Workflow (FIFO)" << endl;
    cout << "    - Stack for Evidence Handling (LIFO)" << endl;
    cout << endl;
    cout << Colors::SUCCESS << "  System initialized successfully!" << Colors::RESET << endl;
    cout << endl;
}

// Display goodbye screen
void UIModule::displayGoodbye() {
    cout << Colors::HEADER << endl;
    cout << "  ============================================================" << endl;
    cout << "                                                              " << endl;
    cout << "              Thank you for using CRIW System!                " << endl;
    cout << "                                                              " << endl;
    cout << "                     Stay safe, stay vigilant.                " << endl;
    cout << "                                                              " << endl;
    cout << "  ============================================================" << endl;
    cout << Colors::RESET << endl;
}

// Get crime type from user
CrimeType UIModule::getCrimeTypeInput() {
    cout << Colors::SUBHEADER << "\n  Select Crime Type:" << Colors::RESET << endl;
    cout << "    [1] Theft         [2] Assault       [3] Burglary" << endl;
    cout << "    [4] Fraud         [5] Vandalism     [6] Robbery" << endl;
    cout << "    [7] Homicide      [8] Kidnapping    [9] Cybercrime" << endl;
    cout << "    [10] Drug Offense [11] Arson        [12] Other" << endl;

    int choice;
    if (!getIntInput(choice, "Enter choice (1-12): ", 1, 12)) {
        return CrimeType::OTHER;
    }
    return static_cast<CrimeType>(choice - 1);
}

// Get investigation status from user
InvestigationStatus UIModule::getStatusInput() {
    cout << Colors::SUBHEADER << "\n  Select Status:" << Colors::RESET << endl;
    cout << "    [1] Pending" << endl;
    cout << "    [2] In Progress" << endl;
    cout << "    [3] Under Review" << endl;
    cout << "    [4] Closed" << endl;
    cout << "    [5] Cold Case" << endl;

    int choice;
    if (!getIntInput(choice, "Enter choice (1-5): ", 1, 5)) {
        return InvestigationStatus::PENDING;
    }
    return static_cast<InvestigationStatus>(choice - 1);
}

// Get evidence type from user
EvidenceType UIModule::getEvidenceTypeInput() {
    cout << Colors::SUBHEADER << "\n  Select Evidence Type:" << Colors::RESET << endl;
    cout << "    [1] Physical" << endl;
    cout << "    [2] Digital" << endl;
    cout << "    [3] Documentary" << endl;
    cout << "    [4] Testimonial" << endl;
    cout << "    [5] Forensic" << endl;
    cout << "    [6] Circumstantial" << endl;

    int choice;
    if (!getIntInput(choice, "Enter choice (1-6): ", 1, 6)) {
        return EvidenceType::PHYSICAL;
    }
    return static_cast<EvidenceType>(choice - 1);
}

// Input crime record details
CrimeRecord UIModule::inputCrimeRecord() {
    CrimeRecord record;
    record.caseID = generateCaseID();

    cout << Colors::HEADER << "\n  === Register New Crime ===" << Colors::RESET << endl;
    cout << Colors::INFO << "  Case ID: " << record.caseID << " (auto-generated)" << Colors::RESET << endl;

    string input;

    cout << Colors::INPUT_PROMPT << "  Crime Title: " << Colors::RESET;
    cin.ignore();
    getline(cin, record.crimeTitle);

    record.crimeType = getCrimeTypeInput();

    cout << Colors::INPUT_PROMPT << "  Description: " << Colors::RESET;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, record.description);

    cout << Colors::INPUT_PROMPT << "  Location: " << Colors::RESET;
    getline(cin, record.location);

    cout << Colors::INPUT_PROMPT << "  Victim Name: " << Colors::RESET;
    getline(cin, record.victimName);

    cout << Colors::INPUT_PROMPT << "  Suspect Name (if known): " << Colors::RESET;
    getline(cin, record.suspectName);
    if (record.suspectName.empty()) record.suspectName = "Unknown";

    cout << Colors::INPUT_PROMPT << "  Reported By: " << Colors::RESET;
    getline(cin, record.reportedBy);

    cout << Colors::INPUT_PROMPT << "  Assigned Officer: " << Colors::RESET;
    getline(cin, record.assignedOfficer);
    if (record.assignedOfficer.empty()) record.assignedOfficer = "Unassigned";

    int priority;
    cout << Colors::INPUT_PROMPT << "  Priority (1-10): " << Colors::RESET;
    cin >> priority;
    record.priorityLevel = (priority >= 1 && priority <= 10) ? priority : 5;

    record.status = InvestigationStatus::PENDING;
    record.dateReported = getCurrentDateTime();

    return record;
}

// Input evidence details
Evidence UIModule::inputEvidence(int caseID) {
    Evidence evidence;
    evidence.evidenceID = ++globalEvidenceIDCounter;
    evidence.relatedCaseID = caseID;

    cout << Colors::HEADER << "\n  === Add Evidence ===" << Colors::RESET << endl;
    cout << Colors::INFO << "  Evidence ID: " << evidence.evidenceID << " (auto-generated)" << Colors::RESET << endl;
    cout << Colors::INFO << "  Related Case: " << caseID << Colors::RESET << endl;

    evidence.type = getEvidenceTypeInput();

    cout << Colors::INPUT_PROMPT << "  Description: " << Colors::RESET;
    cin.ignore();
    getline(cin, evidence.description);

    cout << Colors::INPUT_PROMPT << "  Collected By: " << Colors::RESET;
    getline(cin, evidence.collectedBy);

    cout << Colors::INPUT_PROMPT << "  Storage Location: " << Colors::RESET;
    getline(cin, evidence.storageLocation);
    if (evidence.storageLocation.empty()) evidence.storageLocation = "Evidence Locker";

    evidence.dateCollected = getCurrentDateTime();
    evidence.isProcessed = false;

    return evidence;
}

// Display error message
void UIModule::displayError(const string& message) {
    cout << Colors::ERROR << "  [ERROR] " << message << Colors::RESET << endl;
}

// Display success message
void UIModule::displaySuccess(const string& message) {
    cout << Colors::SUCCESS << "  [SUCCESS] " << message << Colors::RESET << endl;
}

// Display warning message
void UIModule::displayWarning(const string& message) {
    cout << Colors::WARNING << "  [WARNING] " << message << Colors::RESET << endl;
}

// Display info message
void UIModule::displayInfo(const string& message) {
    cout << Colors::INFO << "  [INFO] " << message << Colors::RESET << endl;
}

// Get menu choice
int UIModule::getMenuChoice(int min, int max) {
    int choice;
    cout << Colors::INPUT_PROMPT << "  Enter your choice: " << Colors::RESET;

    if (!(cin >> choice)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return -1;
    }

    if (choice < min || choice > max) {
        return -1;
    }

    return choice;
}

// Confirm action
bool UIModule::confirmAction(const string& message) {
    char response;
    cout << Colors::WARNING << "  " << message << " (y/n): " << Colors::RESET;
    cin >> response;
    return (response == 'y' || response == 'Y');
}

/*
================================================================================
                    CRIME SYSTEM MANAGER IMPLEMENTATION
================================================================================
*/

// Constructor
CrimeSystemManager::CrimeSystemManager()
    : recentActions(50) {
    logAction("System initialized");
}

// Destructor
CrimeSystemManager::~CrimeSystemManager() {
    logAction("System shutdown");
}

// Log an action
void CrimeSystemManager::logAction(const string& action) {
    string logEntry = getCurrentDateTime() + " - " + action;
    recentActions.enqueue(logEntry);
}

// Register new crime
void CrimeSystemManager::registerCrime() {
    CrimeRecord record = UIModule::inputCrimeRecord();
    crimeTree.insert(record);

    // Auto-add to investigation queue
    InvestigationItem item(record.caseID, record.crimeTitle, record.assignedOfficer);
    item.priority = record.priorityLevel;
    investigationQueue.enqueue(item);

    UIModule::displaySuccess("Crime registered successfully with Case ID: " + to_string(record.caseID));
    UIModule::displayInfo("Case automatically added to investigation queue.");
    logAction("Registered crime: Case #" + to_string(record.caseID));
}

// Search crime by ID
void CrimeSystemManager::searchCrime() {
    int caseID;
    cout << Colors::INPUT_PROMPT << "  Enter Case ID to search: " << Colors::RESET;
    cin >> caseID;

    CrimeRecord* record = crimeTree.search(caseID);

    if (record != nullptr) {
        UIModule::displaySuccess("Case found!");
        record->display();
        logAction("Searched crime: Case #" + to_string(caseID) + " - Found");
    }
    else {
        UIModule::displayError("Case #" + to_string(caseID) + " not found in records.");
        logAction("Searched crime: Case #" + to_string(caseID) + " - Not found");
    }
}

// Update crime record
void CrimeSystemManager::updateCrime() {
    int caseID;
    cout << Colors::INPUT_PROMPT << "  Enter Case ID to update: " << Colors::RESET;
    cin >> caseID;

    CrimeRecord* record = crimeTree.search(caseID);

    if (record == nullptr) {
        UIModule::displayError("Case #" + to_string(caseID) + " not found.");
        return;
    }

    cout << Colors::SUBHEADER << "\n  Current Record:" << Colors::RESET << endl;
    record->display();

    cout << Colors::SUBHEADER << "\n  What would you like to update?" << Colors::RESET << endl;
    cout << "    [1] Status" << endl;
    cout << "    [2] Priority" << endl;
    cout << "    [3] Assigned Officer" << endl;
    cout << "    [4] Suspect Name" << endl;
    cout << "    [5] Notes" << endl;
    cout << "    [0] Cancel" << endl;

    int choice = UIModule::getMenuChoice(0, 5);

    switch (choice) {
    case 1:
        record->status = UIModule::getStatusInput();
        break;
    case 2: {
        int priority;
        cout << Colors::INPUT_PROMPT << "  New Priority (1-10): " << Colors::RESET;
        cin >> priority;
        record->priorityLevel = (priority >= 1 && priority <= 10) ? priority : record->priorityLevel;
        break;
    }
    case 3:
        cout << Colors::INPUT_PROMPT << "  New Officer: " << Colors::RESET;
        cin.ignore();
        getline(cin, record->assignedOfficer);
        break;
    case 4:
        cout << Colors::INPUT_PROMPT << "  Suspect Name: " << Colors::RESET;
        cin.ignore();
        getline(cin, record->suspectName);
        break;
    case 5:
        cout << Colors::INPUT_PROMPT << "  Add Notes: " << Colors::RESET;
        cin.ignore();
        getline(cin, record->notes);
        break;
    case 0:
        UIModule::displayInfo("Update cancelled.");
        return;
    default:
        UIModule::displayError("Invalid choice.");
        return;
    }

    UIModule::displaySuccess("Record updated successfully.");
    logAction("Updated crime: Case #" + to_string(caseID));
}

// Delete crime record
void CrimeSystemManager::deleteCrime() {
    int caseID;
    cout << Colors::INPUT_PROMPT << "  Enter Case ID to delete: " << Colors::RESET;
    cin >> caseID;

    CrimeRecord* record = crimeTree.search(caseID);

    if (record == nullptr) {
        UIModule::displayError("Case #" + to_string(caseID) + " not found.");
        return;
    }

    record->display();

    if (UIModule::confirmAction("Are you sure you want to delete this record?")) {
        if (crimeTree.remove(caseID)) {
            UIModule::displaySuccess("Record deleted successfully.");
            logAction("Deleted crime: Case #" + to_string(caseID));
        }
        else {
            UIModule::displayError("Failed to delete record.");
        }
    }
    else {
        UIModule::displayInfo("Deletion cancelled.");
    }
}

// View all crimes
void CrimeSystemManager::viewAllCrimes() {
    vector<CrimeRecord> records = crimeTree.inorderTraversal();

    if (records.empty()) {
        UIModule::displayWarning("No crime records in the system.");
        return;
    }

    ReportingModule::displayAllRecords(records);
    logAction("Viewed all crimes");
}

// View crimes by traversal type
void CrimeSystemManager::viewByTraversal() {
    cout << Colors::SUBHEADER << "\n  Select Traversal Order:" << Colors::RESET << endl;
    cout << "    [1] Inorder (Sorted by Case ID)" << endl;
    cout << "    [2] Preorder (Root first)" << endl;
    cout << "    [3] Postorder (Root last)" << endl;

    int choice = UIModule::getMenuChoice(1, 3);

    vector<CrimeRecord> records;
    string traversalType;

    switch (choice) {
    case 1:
        records = crimeTree.inorderTraversal();
        traversalType = "Inorder";
        break;
    case 2:
        records = crimeTree.preorderTraversal();
        traversalType = "Preorder";
        break;
    case 3:
        records = crimeTree.postorderTraversal();
        traversalType = "Postorder";
        break;
    default:
        return;
    }

    if (records.empty()) {
        UIModule::displayWarning("No records to display.");
        return;
    }

    cout << Colors::HEADER << "\n  === " << traversalType << " Traversal ===" << Colors::RESET << endl;
    cout << Colors::INFO << "  Displaying " << records.size() << " records" << Colors::RESET << endl;

    for (const auto& record : records) {
        cout << "  - Case #" << record.caseID << ": " << record.crimeTitle << endl;
    }

    logAction("Viewed crimes using " + traversalType + " traversal");
}

// Display AVL tree structure
void CrimeSystemManager::displayCrimeTree() {
    crimeTree.displayTree();
    cout << Colors::INFO << "\n  Tree Height: " << crimeTree.height() << Colors::RESET << endl;
    cout << Colors::INFO << "  Total Nodes: " << crimeTree.size() << Colors::RESET << endl;
    logAction("Displayed AVL tree structure");
}

// Add to investigation queue
void CrimeSystemManager::addToInvestigation() {
    int caseID;
    cout << Colors::INPUT_PROMPT << "  Enter Case ID to add to queue: " << Colors::RESET;
    cin >> caseID;

    CrimeRecord* record = crimeTree.search(caseID);

    if (record == nullptr) {
        UIModule::displayError("Case #" + to_string(caseID) + " not found.");
        return;
    }

    InvestigationItem item(record->caseID, record->crimeTitle, record->assignedOfficer);
    item.priority = record->priorityLevel;
    item.status = record->status;

    investigationQueue.enqueue(item);

    UIModule::displaySuccess("Case added to investigation queue.");
    UIModule::displayInfo("Queue position: " + to_string(investigationQueue.size()));
    logAction("Added to queue: Case #" + to_string(caseID));
}

// Process next investigation
void CrimeSystemManager::processNextInvestigation() {
    if (investigationQueue.isEmpty()) {
        UIModule::displayWarning("Investigation queue is empty.");
        return;
    }

    InvestigationItem item = investigationQueue.dequeue();

    cout << Colors::HEADER << "\n  === Processing Investigation ===" << Colors::RESET << endl;
    item.display();

    // Update crime record status if exists
    CrimeRecord* record = crimeTree.search(item.caseID);
    if (record != nullptr) {
        record->status = InvestigationStatus::IN_PROGRESS;
        UIModule::displayInfo("Case status updated to: In Progress");
    }

    UIModule::displaySuccess("Case dequeued for investigation.");
    UIModule::displayInfo("Remaining in queue: " + to_string(investigationQueue.size()));
    logAction("Processed investigation: Case #" + to_string(item.caseID));
}

// View investigation queue
void CrimeSystemManager::viewInvestigationQueue() {
    investigationQueue.display();
    logAction("Viewed investigation queue");
}

// Check queue status
void CrimeSystemManager::checkQueueStatus() {
    cout << Colors::HEADER << "\n  === Queue Status ===" << Colors::RESET << endl;
    cout << "  Cases in queue: " << investigationQueue.size() << endl;
    cout << "  Queue empty: " << (investigationQueue.isEmpty() ? "Yes" : "No") << endl;

    if (!investigationQueue.isEmpty()) {
        cout << Colors::SUBHEADER << "\n  Next case to process:" << Colors::RESET << endl;
        investigationQueue.peek().display();
    }
}

// Add evidence
void CrimeSystemManager::addEvidence() {
    int caseID;
    cout << Colors::INPUT_PROMPT << "  Enter Case ID for evidence: " << Colors::RESET;
    cin >> caseID;

    CrimeRecord* record = crimeTree.search(caseID);

    if (record == nullptr) {
        UIModule::displayError("Case #" + to_string(caseID) + " not found.");
        return;
    }

    Evidence evidence = UIModule::inputEvidence(caseID);
    evidenceStack.push(evidence);

    UIModule::displaySuccess("Evidence added to stack.");
    UIModule::displayInfo("Total evidence items: " + to_string(evidenceStack.size()));
    logAction("Added evidence #" + to_string(evidence.evidenceID) + " for Case #" + to_string(caseID));
}

// Process evidence
void CrimeSystemManager::processEvidence() {
    if (evidenceStack.isEmpty()) {
        UIModule::displayWarning("Evidence stack is empty.");
        return;
    }

    Evidence evidence = evidenceStack.pop();
    evidence.isProcessed = true;

    cout << Colors::HEADER << "\n  === Processing Evidence ===" << Colors::RESET << endl;
    evidence.display();

    UIModule::displaySuccess("Evidence processed and removed from stack.");
    UIModule::displayInfo("Remaining evidence items: " + to_string(evidenceStack.size()));
    logAction("Processed evidence #" + to_string(evidence.evidenceID));
}

// View evidence stack
void CrimeSystemManager::viewEvidenceStack() {
    evidenceStack.display();
    logAction("Viewed evidence stack");
}

// Analyze evidence (expression evaluation)
void CrimeSystemManager::analyzeEvidence() {
    cout << Colors::HEADER << "\n  === Expression Calculator ===" << Colors::RESET << endl;
    cout << Colors::INFO << "  Uses stack-based evaluation (infix to postfix)" << Colors::RESET << endl;
    cout << Colors::INFO << "  Supported operators: + - * / ^ %" << Colors::RESET << endl;

    string expression;
    cout << Colors::INPUT_PROMPT << "  Enter infix expression: " << Colors::RESET;
    cin.ignore();
    getline(cin, expression);

    try {
        string postfix = evaluator.infixToPostfix(expression);
        double result = evaluator.evaluatePostfix(postfix);

        cout << Colors::SUBHEADER << "\n  Results:" << Colors::RESET << endl;
        cout << "  Infix:   " << expression << endl;
        cout << "  Postfix: " << postfix << endl;
        cout << Colors::SUCCESS << "  Result:  " << result << Colors::RESET << endl;

        logAction("Evaluated expression: " + expression);
    }
    catch (const exception& e) {
        UIModule::displayError("Evaluation error: " + string(e.what()));
    }
}

// Convert values
void CrimeSystemManager::convertValues() {
    cout << Colors::HEADER << "\n  === Decimal to Binary Converter ===" << Colors::RESET << endl;
    cout << Colors::INFO << "  Uses stack to store remainders" << Colors::RESET << endl;

    int decimal;
    cout << Colors::INPUT_PROMPT << "  Enter decimal number: " << Colors::RESET;
    cin >> decimal;

    string binary = evaluator.decimalToBinary(decimal);

    cout << Colors::SUBHEADER << "\n  Result:" << Colors::RESET << endl;
    cout << "  Decimal: " << decimal << endl;
    cout << Colors::SUCCESS << "  Binary:  " << binary << Colors::RESET << endl;

    logAction("Converted " + to_string(decimal) + " to binary");
}

// Generate full report
void CrimeSystemManager::generateReport() {
    vector<CrimeRecord> records = crimeTree.inorderTraversal();

    if (records.empty()) {
        UIModule::displayWarning("No records to generate report.");
        return;
    }

    CrimeStatistics stats = ReportingModule::generateStatistics(records);
    stats.display();

    ReportingModule::displayPriorityChart(stats);
    ReportingModule::displayCrimeTypeChart(stats);

    logAction("Generated full report");
}

// Generate statistics
void CrimeSystemManager::generateStatistics() {
    vector<CrimeRecord> records = crimeTree.inorderTraversal();

    if (records.empty()) {
        UIModule::displayWarning("No records for statistics.");
        return;
    }

    CrimeStatistics stats = ReportingModule::generateStatistics(records);
    stats.display();

    logAction("Generated statistics");
}

// Search crimes by criteria
void CrimeSystemManager::searchCrimesByCriteria() {
    cout << Colors::SUBHEADER << "\n  Search By:" << Colors::RESET << endl;
    cout << "    [1] Crime Type" << endl;
    cout << "    [2] Status" << endl;
    cout << "    [3] Location" << endl;

    int choice = UIModule::getMenuChoice(1, 3);

    vector<CrimeRecord> allRecords = crimeTree.inorderTraversal();
    vector<CrimeRecord> results;

    switch (choice) {
    case 1: {
        CrimeType type = UIModule::getCrimeTypeInput();
        results = SearchingAlgorithms::searchByCrimeType(allRecords, type);
        break;
    }
    case 2: {
        InvestigationStatus status = UIModule::getStatusInput();
        results = SearchingAlgorithms::searchByStatus(allRecords, status);
        break;
    }
    case 3: {
        string location;
        cout << Colors::INPUT_PROMPT << "  Enter location: " << Colors::RESET;
        cin.ignore();
        getline(cin, location);
        results = SearchingAlgorithms::searchByLocation(allRecords, location);
        break;
    }
    default:
        return;
    }

    if (results.empty()) {
        UIModule::displayWarning("No matching records found.");
    }
    else {
        cout << Colors::SUCCESS << "\n  Found " << results.size() << " matching records:" << Colors::RESET << endl;
        for (const auto& record : results) {
            cout << "  - Case #" << record.caseID << ": " << record.crimeTitle << endl;
        }
    }

    logAction("Searched by criteria");
}

// Sort and display records
void CrimeSystemManager::sortAndDisplay() {
    vector<CrimeRecord> records = crimeTree.inorderTraversal();

    if (records.empty()) {
        UIModule::displayWarning("No records to sort.");
        return;
    }

    cout << Colors::SUBHEADER << "\n  Sort By:" << Colors::RESET << endl;
    cout << "    [1] Case ID (ascending)" << endl;
    cout << "    [2] Priority (descending)" << endl;
    cout << "    [3] Date (ascending)" << endl;

    int sortChoice = UIModule::getMenuChoice(1, 3);

    cout << Colors::SUBHEADER << "\n  Algorithm:" << Colors::RESET << endl;
    cout << "    [1] Insertion Sort" << endl;
    cout << "    [2] Quick Sort" << endl;
    cout << "    [3] Merge Sort" << endl;

    int algoChoice = UIModule::getMenuChoice(1, 3);

    string algorithm;
    switch (algoChoice) {
    case 1: algorithm = "insertion"; break;
    case 2: algorithm = "quick"; break;
    case 3: algorithm = "merge"; break;
    default: algorithm = "quick"; break;
    }

    switch (sortChoice) {
    case 1:
        SortingAlgorithms::sortByCaseID(records, algorithm);
        break;
    case 2:
        SortingAlgorithms::sortByPriority(records, algorithm);
        break;
    case 3:
        SortingAlgorithms::sortByDate(records, algorithm);
        break;
    default:
        return;
    }

    ReportingModule::displayAllRecords(records);
    logAction("Sorted and displayed records");
}

// Compare algorithms
void CrimeSystemManager::compareAlgorithms() {
    vector<CrimeRecord> records = crimeTree.inorderTraversal();

    cout << Colors::SUBHEADER << "\n  Compare:" << Colors::RESET << endl;
    cout << "    [1] Searching Algorithms" << endl;
    cout << "    [2] Sorting Algorithms" << endl;

    int choice = UIModule::getMenuChoice(1, 2);

    switch (choice) {
    case 1: {
        if (records.empty()) {
            UIModule::displayWarning("No records for comparison.");
            return;
        }
        int searchKey;
        cout << Colors::INPUT_PROMPT << "  Enter Case ID to search: " << Colors::RESET;
        cin >> searchKey;
        ReportingModule::compareSearchAlgorithms(records, searchKey);
        break;
    }
    case 2:
        ReportingModule::compareSortingAlgorithms(records);
        break;
    default:
        return;
    }

    logAction("Compared algorithms");
}

// Display complexities
void CrimeSystemManager::displayComplexities() {
    cout << Colors::SUBHEADER << "\n  Select Analysis:" << Colors::RESET << endl;
    cout << "    [1] AVL Tree" << endl;
    cout << "    [2] Queue" << endl;
    cout << "    [3] Stack" << endl;
    cout << "    [4] Sorting" << endl;
    cout << "    [5] Searching" << endl;
    cout << "    [6] All" << endl;

    int choice = UIModule::getMenuChoice(1, 6);

    switch (choice) {
    case 1:
        AlgorithmAnalysis::displayAVLComplexity();
        break;
    case 2:
        AlgorithmAnalysis::displayQueueComplexity();
        break;
    case 3:
        AlgorithmAnalysis::displayStackComplexity();
        break;
    case 4:
        AlgorithmAnalysis::displaySortingComplexity();
        break;
    case 5:
        AlgorithmAnalysis::displaySearchingComplexity();
        break;
    case 6:
        AlgorithmAnalysis::displayFullAnalysis();
        break;
    default:
        return;
    }

    logAction("Displayed complexity analysis");
}

// Display design decisions
void CrimeSystemManager::displayDesignDecisions() {
    AlgorithmAnalysis::displayDesignDecisions();
    logAction("Displayed design decisions");
}

// View recent actions
void CrimeSystemManager::viewRecentActions() {
    cout << Colors::HEADER << "\n  === Recent Actions Log ===" << Colors::RESET << endl;
    recentActions.display();
}

// Add sample data for testing
void CrimeSystemManager::addSampleData() {
    UIModule::displayInfo("Adding sample crime records...");

    // Sample crime 1
    CrimeRecord crime1(generateCaseID(), "Downtown Bank Robbery", CrimeType::ROBBERY,
        "Armed robbery at First National Bank", "123 Main Street");
    crime1.victimName = "First National Bank";
    crime1.suspectName = "Unknown masked individual";
    crime1.assignedOfficer = "Det. John Smith";
    crime1.priorityLevel = 9;
    crimeTree.insert(crime1);

    // Sample crime 2
    CrimeRecord crime2(generateCaseID(), "Vehicle Theft", CrimeType::THEFT,
        "Blue Honda Civic stolen from parking lot", "Central Mall Parking");
    crime2.victimName = "Michael Johnson";
    crime2.assignedOfficer = "Off. Sarah Brown";
    crime2.priorityLevel = 6;
    crimeTree.insert(crime2);

    // Sample crime 3
    CrimeRecord crime3(generateCaseID(), "Residential Burglary", CrimeType::BURGLARY,
        "Home break-in during vacation", "456 Oak Avenue");
    crime3.victimName = "Williams Family";
    crime3.assignedOfficer = "Det. Mike Wilson";
    crime3.priorityLevel = 7;
    crimeTree.insert(crime3);

    // Sample crime 4
    CrimeRecord crime4(generateCaseID(), "Online Fraud Scheme", CrimeType::FRAUD,
        "Phishing attack targeting elderly", "Online");
    crime4.victimName = "Multiple victims";
    crime4.suspectName = "Unknown hacker group";
    crime4.assignedOfficer = "Cyber Unit";
    crime4.priorityLevel = 8;
    crimeTree.insert(crime4);

    // Sample crime 5
    CrimeRecord crime5(generateCaseID(), "Street Assault", CrimeType::ASSAULT,
        "Assault outside nightclub", "789 Club Street");
    crime5.victimName = "Robert Taylor";
    crime5.suspectName = "James Miller";
    crime5.assignedOfficer = "Off. Lisa Davis";
    crime5.priorityLevel = 7;
    crimeTree.insert(crime5);

    // Sample crime 6
    CrimeRecord crime6(generateCaseID(), "Drug Trafficking", CrimeType::DRUG_OFFENSE,
        "Large quantity of narcotics seized", "Industrial District");
    crime6.suspectName = "Multiple suspects";
    crime6.assignedOfficer = "Narcotics Unit";
    crime6.priorityLevel = 10;
    crimeTree.insert(crime6);

    // Sample crime 7
    CrimeRecord crime7(generateCaseID(), "Vandalism at School", CrimeType::VANDALISM,
        "Graffiti and property damage", "Lincoln High School");
    crime7.victimName = "Lincoln High School";
    crime7.assignedOfficer = "Off. Tom Anderson";
    crime7.priorityLevel = 4;
    crimeTree.insert(crime7);

    // Sample crime 8
    CrimeRecord crime8(generateCaseID(), "Identity Theft", CrimeType::CYBERCRIME,
        "Stolen personal information used for credit fraud", "Online");
    crime8.victimName = "Jennifer White";
    crime8.assignedOfficer = "Cyber Unit";
    crime8.priorityLevel = 6;
    crimeTree.insert(crime8);

    // Add to investigation queue
    for (int id = crime1.caseID; id <= crime8.caseID; id++) {
        CrimeRecord* record = crimeTree.search(id);
        if (record != nullptr) {
            InvestigationItem item(record->caseID, record->crimeTitle, record->assignedOfficer);
            item.priority = record->priorityLevel;
            investigationQueue.enqueue(item);
        }
    }

    // Add sample evidence
    Evidence ev1(++globalEvidenceIDCounter, crime1.caseID, EvidenceType::DIGITAL,
        "Security camera footage from bank");
    ev1.collectedBy = "Det. John Smith";
    evidenceStack.push(ev1);

    Evidence ev2(++globalEvidenceIDCounter, crime1.caseID, EvidenceType::PHYSICAL,
        "Fingerprints from counter");
    ev2.collectedBy = "Forensics Team";
    evidenceStack.push(ev2);

    Evidence ev3(++globalEvidenceIDCounter, crime3.caseID, EvidenceType::PHYSICAL,
        "Broken window glass fragments");
    ev3.collectedBy = "CSI Unit";
    evidenceStack.push(ev3);

    UIModule::displaySuccess("Added 8 sample crime records");
    UIModule::displaySuccess("Added 8 cases to investigation queue");
    UIModule::displaySuccess("Added 3 evidence items to stack");

    logAction("Added sample data");
}

// Handle main menu
void CrimeSystemManager::handleMainMenu() {
    int choice = UIModule::getMenuChoice(0, 6);

    switch (choice) {
    case 1:
        handleCrimeRecordMenu();
        break;
    case 2:
        handleInvestigationMenu();
        break;
    case 3:
        handleEvidenceMenu();
        break;
    case 4:
        handleReportingMenu();
        break;
    case 5:
        handleAlgorithmMenu();
        break;
    case 6:
        addSampleData();
        break;
    case 0:
        UIModule::displayGoodbye();
        exit(0);
    default:
        UIModule::displayError("Invalid choice. Please try again.");
    }
}

// Handle crime record menu
void CrimeSystemManager::handleCrimeRecordMenu() {
    bool back = false;

    while (!back) {
        UIModule::displayCrimeRecordMenu();
        int choice = UIModule::getMenuChoice(0, 7);

        switch (choice) {
        case 1:
            registerCrime();
            break;
        case 2:
            searchCrime();
            break;
        case 3:
            updateCrime();
            break;
        case 4:
            deleteCrime();
            break;
        case 5:
            viewAllCrimes();
            break;
        case 6:
            viewByTraversal();
            break;
        case 7:
            displayCrimeTree();
            break;
        case 0:
            back = true;
            break;
        default:
            UIModule::displayError("Invalid choice.");
        }

        if (!back) {
            cout << Colors::INPUT_PROMPT << "\n  Press Enter to continue..." << Colors::RESET;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
        }
    }
}

// Handle investigation menu
void CrimeSystemManager::handleInvestigationMenu() {
    bool back = false;

    while (!back) {
        UIModule::displayInvestigationMenu();
        int choice = UIModule::getMenuChoice(0, 4);

        switch (choice) {
        case 1:
            addToInvestigation();
            break;
        case 2:
            processNextInvestigation();
            break;
        case 3:
            checkQueueStatus();
            break;
        case 4:
            viewInvestigationQueue();
            break;
        case 0:
            back = true;
            break;
        default:
            UIModule::displayError("Invalid choice.");
        }

        if (!back) {
            cout << Colors::INPUT_PROMPT << "\n  Press Enter to continue..." << Colors::RESET;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
        }
    }
}

// Handle evidence menu
void CrimeSystemManager::handleEvidenceMenu() {
    bool back = false;

    while (!back) {
        UIModule::displayEvidenceMenu();
        int choice = UIModule::getMenuChoice(0, 5);

        switch (choice) {
        case 1:
            addEvidence();
            break;
        case 2:
            processEvidence();
            break;
        case 3:
            viewEvidenceStack();
            break;
        case 4:
            analyzeEvidence();
            break;
        case 5:
            convertValues();
            break;
        case 0:
            back = true;
            break;
        default:
            UIModule::displayError("Invalid choice.");
        }

        if (!back) {
            cout << Colors::INPUT_PROMPT << "\n  Press Enter to continue..." << Colors::RESET;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
        }
    }
}

// Handle reporting menu
void CrimeSystemManager::handleReportingMenu() {
    bool back = false;

    while (!back) {
        UIModule::displayReportingMenu();
        int choice = UIModule::getMenuChoice(0, 7);

        switch (choice) {
        case 1:
            generateReport();
            break;
        case 2: {
            vector<CrimeRecord> records = crimeTree.inorderTraversal();
            CrimeStatistics stats = ReportingModule::generateStatistics(records);
            ReportingModule::displayPriorityChart(stats);
            break;
        }
        case 3: {
            vector<CrimeRecord> records = crimeTree.inorderTraversal();
            CrimeStatistics stats = ReportingModule::generateStatistics(records);
            ReportingModule::displayCrimeTypeChart(stats);
            break;
        }
        case 4:
            searchCrimesByCriteria();
            break;
        case 5:
            sortAndDisplay();
            break;
        case 6:
        case 7:
            compareAlgorithms();
            break;
        case 0:
            back = true;
            break;
        default:
            UIModule::displayError("Invalid choice.");
        }

        if (!back) {
            cout << Colors::INPUT_PROMPT << "\n  Press Enter to continue..." << Colors::RESET;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
        }
    }
}

// Handle algorithm menu
void CrimeSystemManager::handleAlgorithmMenu() {
    bool back = false;

    while (!back) {
        UIModule::displayAlgorithmMenu();
        int choice = UIModule::getMenuChoice(0, 8);

        switch (choice) {
        case 1:
            AlgorithmAnalysis::displayAVLComplexity();
            break;
        case 2:
            AlgorithmAnalysis::displayQueueComplexity();
            break;
        case 3:
            AlgorithmAnalysis::displayStackComplexity();
            break;
        case 4:
            AlgorithmAnalysis::displaySortingComplexity();
            break;
        case 5:
            AlgorithmAnalysis::displaySearchingComplexity();
            break;
        case 6:
            AlgorithmAnalysis::displayFullAnalysis();
            break;
        case 7:
            AlgorithmAnalysis::displayComparisonTable();
            break;
        case 8:
            displayDesignDecisions();
            break;
        case 0:
            back = true;
            break;
        default:
            UIModule::displayError("Invalid choice.");
        }

        if (!back) {
            cout << Colors::INPUT_PROMPT << "\n  Press Enter to continue..." << Colors::RESET;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
        }
    }
}

// Run the main system loop
void CrimeSystemManager::run() {
    UIModule::displayWelcome();

    cout << Colors::INPUT_PROMPT << "\n  Press Enter to start..." << Colors::RESET;
    cin.get();

    while (true) {
        UIModule::displayMainMenu();
        handleMainMenu();
    }
}

/*
================================================================================
                    MAIN FUNCTION
================================================================================
*/

int main() {
    try {
        CrimeSystemManager system;
        system.run();
    }
    catch (const exception& e) {
        cerr << Colors::ERROR << "Fatal error: " << e.what() << Colors::RESET << endl;
        return 1;
    }

    return 0;
}

