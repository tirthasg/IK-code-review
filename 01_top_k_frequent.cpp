// Helper function to implement strategy of any arbitrary worker
void Helper(vector<vector<int>> &nums, int start, int end, int index)
{
    // Base case or work done by leaf level worker
    if (start == end)
        return;
    
    // Work done by arbitrary worker in the hierarchy
    // Selecting a random index in our sub-array 
    int randIndex = start + rand() % (end - start + 1);

    // Swapping the element at random index with the element at starting index
    swap(nums[start], nums[randIndex]);
    
    // Storing the pivot into a temp variable of type vector<int>
    auto pivot = nums[start];

    // Lomuto's partition
    int smaller = start;
    for (int bigger = smaller + 1; bigger <= end; ++bigger)
        // Comparison is done based on frequency
        if (nums[bigger][1] <= pivot[1])
            swap(nums[++smaller], nums[bigger]);
    
    // Swapping with the location of pivot
    swap(nums[start], nums[smaller]);
    
    // Lucky case where the chosen pivot is the k'th most frequent element
    if (smaller == index)
        return;
    
    // Recursively perfom Quick Select on right sub-array
    if (smaller < index) {
        Helper(nums, smaller + 1, end, index);
        return;
    }
    
    // Recursively perform Quick Select on left sub-array
    Helper(nums, start, smaller - 1, index);
}

// Quick Select implementation returning the top k frequent elements as a vector
vector<int> QuickSelect(vector<vector<int>> &nums, int k)
{
    int N = nums.size();
    vector<int> result;
    
    // Seeding random number generator
    srand(time(0));

    // Calling Helper function to implement the Quick Select startegy recursively
    Helper(nums, 0, N - 1, N - k);
    
    // Saving the top k frequent elements in resultant vector
    for (int i = N - k; i < N; ++i)
        result.push_back(nums[i][0]);
        
    return result;
}

// Main function
vector<int> find_top_k_frequent_elements(vector<int> &arr, int k) {
    // Write your code here.
    int N = arr.size();

    // Storing the frequency table as a hashmap    
    unordered_map<int, int> hmap;
    for (int i = 0; i < N; ++i)
        if (hmap.count(arr[i]))
            hmap[arr[i]]++;
        else
            hmap[arr[i]] = 1;
    
    // Creating a vector of vector from the hashmap
    // Each vector stores element & it's corresponding frequency
    vector<vector<int>> nums;
    for (auto kvp: hmap)
        nums.push_back({kvp.first, kvp.second});

    // Calling Quick Select to return top k frequent elements as a vector        
    return QuickSelect(nums, k);
}
