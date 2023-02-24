// Function to calculate distance of any point from the reference point
// Actually the square of distance 
// Saving computation time by not performing the square root operation
long long Distance(vector<int> &point, int p_x, int p_y)
{
    long long xDiff = point[0] - p_x;
    long long yDiff = point[1] - p_y;
    
    return xDiff * xDiff + yDiff * yDiff;
}

// Helper function to implement strategy of any arbitrary worker
void Helper(vector<vector<int>> &n_points, int start, int end, int index, int p_x, int p_y)
{
    // Base case or work done by leaf level worker
    if (start == end)
        return;
    
    // Work done by arbitrary worker in the hierarchy
    // Selecting a random index in our sub-array 
    int randIndex = start + rand() % (end - start + 1);

    // Swapping the element at random index with the element at starting index
    swap(n_points[start], n_points[randIndex]);
    
    // Storing the pivot into a temp variable of type vector<int> 
    auto pivot = n_points[start];

    // Calculating the distance of pivot from the reference point
    long long pivotDist = Distance(pivot, p_x, p_y);
    
    // Lomuto's partition
    int smaller = start;
    for (int bigger = start + 1; bigger <= end; ++bigger)
        // Comparison is done based on distance from reference point
        if (Distance(n_points[bigger], p_x, p_y) <= pivotDist)
            swap(n_points[++smaller], n_points[bigger]);
    
    // Swapping with the location of pivot
    swap(n_points[start], n_points[smaller]);
    
    // Lucky case where the chosen pivot is the k'th most frequent element
    if (smaller == index)
        return;
    
    // Recursively perfom Quick Select on right sub-array
    if (smaller < index) {
        Helper(n_points, smaller + 1, end, index, p_x, p_y);
        return;
    }
    
    // Recursively perform Quick Select on left sub-array
    Helper(n_points, start, smaller - 1, index, p_x, p_y);
}

// Main code
vector<vector<int>> nearest_neighbours(int p_x, int p_y, int k, vector<vector<int>> &n_points) {
    // Write your code here.
    int N = n_points.size();
    vector<vector<int>> result(k);
    
    // Seeding the random number generator
    srand(time(0));

    // Calling Helper function to implement the Quick Select startegy recursively
    Helper(n_points, 0, N - 1, k - 1, p_x, p_y);
    
    // Saving the k nearest points in resultant vector
    for (int i = 0; i < k; ++i)
        result[i] = n_points[i];
    
    return result;
}
