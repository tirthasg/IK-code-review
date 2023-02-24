long long Distance(vector<int> &point, int p_x, int p_y)
{
    long long xDiff = point[0] - p_x;
    long long yDiff = point[1] - p_y;
    
    return xDiff * xDiff + yDiff * yDiff;
}

void Helper(vector<vector<int>> &n_points, int start, int end, int index, int p_x, int p_y)
{
    if (start == end)
        return;
        
    int randIndex = start + rand() % (end - start + 1);
    swap(n_points[start], n_points[randIndex]);
    
    auto pivot = n_points[start];
    long long pivotDist = Distance(pivot, p_x, p_y);
    
    int smaller = start;
    for (int bigger = start + 1; bigger <= end; ++bigger)
        if (Distance(n_points[bigger], p_x, p_y) <= pivotDist)
            swap(n_points[++smaller], n_points[bigger]);
    
    swap(n_points[start], n_points[smaller]);
    
    if (smaller == index)
        return;
        
    if (smaller < index) {
        Helper(n_points, smaller + 1, end, index, p_x, p_y);
        return;
    }
    
    Helper(n_points, start, smaller - 1, index, p_x, p_y);
}

vector<vector<int>> nearest_neighbours(int p_x, int p_y, int k, vector<vector<int>> &n_points) {
    // Write your code here.
    int N = n_points.size();
    vector<vector<int>> result(k);
        
    srand(time(0));
    Helper(n_points, 0, N - 1, k - 1, p_x, p_y);
    
    for (int i = 0; i < k; ++i)
        result[i] = n_points[i];
    
    return result;
}
