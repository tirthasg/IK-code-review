void Helper(vector<vector<int>> &nums, int start, int end, int index)
{
    if (start == end)
        return;
        
    int randIndex = start + rand() % (end - start + 1);
    swap(nums[start], nums[randIndex]);
    
    auto pivot = nums[start];
    int smaller = start;
    for (int bigger = smaller + 1; bigger <= end; ++bigger)
        if (nums[bigger][1] <= pivot[1])
            swap(nums[++smaller], nums[bigger]);
        
    swap(nums[start], nums[smaller]);
    
    if (smaller == index)
        return;
        
    if (smaller < index) {
        Helper(nums, smaller + 1, end, index);
        return;
    }
    
    Helper(nums, start, smaller - 1, index);
}

vector<int> QuickSelect(vector<vector<int>> &nums, int k)
{
    int N = nums.size();
    vector<int> result;
    
    srand(time(0));
    Helper(nums, 0, N - 1, N - k);
    
    for (int i = N - k; i < N; ++i)
        result.push_back(nums[i][0]);
        
    return result;
}


vector<int> find_top_k_frequent_elements(vector<int> &arr, int k) {
    // Write your code here.
    int N = arr.size();
    
    unordered_map<int, int> hmap;
    for (int i = 0; i < N; ++i)
        if (hmap.count(arr[i]))
            hmap[arr[i]]++;
        else
            hmap[arr[i]] = 1;
    
    vector<vector<int>> nums;
    for (auto kvp: hmap)
        nums.push_back({kvp.first, kvp.second});
        
    return QuickSelect(nums, k);
}
