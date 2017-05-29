#include <iostream>
using namespace std;

// class CastleBuilder
// Build castles following AEQ rules
class CastleBuilder
{
public:
    // Method: getCastleCount()
    //
    // Description
    //      Reads topography array and returns the number of
    //      castles that can be built following AEQ rules
    //
    // Params:
    //      topography  - integer array that represent topography of the land
    //      size        - size of topography array 
    //
    // Return:
    //      Number of castles
    //
    // AEQ rules:
    //      1.  Build castles only on peaks or in valleys
    //      2.  First value in topography list is always castle 
    //      3.  Series of the same integers are treated as a single topography value
    int getCastleCount(const int* const topography, int size)
    {
        if (size <= 0 || topography == nullptr)
        {     
            // No place to build castle here  
            return 0;
        }
            
        // We can build at least one castle now
        int castleCount = 1;                
        Direction oldDirection = Undefined;
        
        // Loop through topography array and see if we can 
        // find any peak or valley to build castle
        for(int i = 1; i < size; i++)
        {
            // Ignore if there is no change in elevation
            if(topography[i-1] != topography[i])
            {
                // Find current elevation direction
                Direction direction = (topography[i-1] < topography[i]) ? DirectionUp : DirectionDown;
                
                // Check if we changed elevation direction
                if(oldDirection != Undefined && oldDirection != direction)
                {
                    // Elevation direction changed! Must be peak 
                    // or vallley - we can build castle here
                    castleCount++;
                }

                // Update with current elevation direction
                oldDirection = direction;
            }
        }

        return castleCount;
    }

private:
    enum Direction {Undefined, DirectionUp, DirectionDown};
};

// class Test
// Test CastleBuilder ability in castle building business
class Test
{
public:
    Test() : testCount(0){}

    void run()
    {
        // Test 1
        test((int[]){}, 0, 0);

        // Test 2
        test((int[1]){1}, 1, 1);

        // Test 3
        test((int[3]){2,2,2}, 3, 1);

        // Test 4 
        test((int[3]){-1,1,2}, 3, 1);

        // Test 5
        test((int[5]){-2,0,2,3,4}, 5, 1);

        // Test 6
        test((int[7]){9,6,6,5,4,-1,-3}, 7, 1);

        // Test 7
        test((int[5]){-4,-4,-3,5,-2}, 5, 2);

        // Test 8
        test((int[3]){1,-3,-1}, 3, 2);

        // Test 9
        test((int[3]){9,-4,5}, 3, 2);

        // Test 10
        test((int[9]){-1,1,1,3,3,3,1,1,-8}, 9, 2);

        // Test 11
        test((int[12]){9,9,9,9,4,4,4,-8,-5,5,5,5}, 12, 2);

        // Test 12
        test((int[14]){9,-4,5,6,-7,3,4,5,6,7,2,2,-3,3}, 14, 6);

        // Test 13
        test((int[15]){4,4,5,5,6,7,-2,-2,6,2,9,3,4,-7,3}, 15, 9);

        cout << "* Successfully passed all " << testCount << " tests" << endl;
    }
    
private:
    int testCount;

    // Use CastleBuilder to find number of castles that can
    // be built and compare result with expected result
    void test(const int* const topography, int size, int expectedResult)
    {
        ++testCount;
        try
        {
            CastleBuilder builder;
            int result = builder.getCastleCount(topography, size);
            if(expectedResult != result)
            {
                cout << "* Failed test #" << testCount << ": result=" << 
                    result << ", expectedResult=" << expectedResult << endl; 
                    
                exit(1);
            }
        }
        catch (...)
        {
            // In real castle builder we will handle more specific 
            // exceptions instead of one generic catch. Now, report error and exit.
            cout << "Unknown fatal error. End of program." << endl;
            exit(2);
        }
    }
}; 

// Program main function
int main()
{
    Test test;
    test.run();
    
    return 0;
}
