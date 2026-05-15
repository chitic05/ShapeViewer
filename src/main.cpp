#include "Page/pageManager.h"
#include "Shape/shapeManager.h"
#include "Shape/shapeRepository.h"
#include "customExceptions.h"
#include <iostream>
#include <cmath>

// ===========================================================
// CERINTA 1: Stack Unwinding Demonstration
// Clasa cu destructor pentru a demonstra stack unwinding
// ===========================================================
class ResourceHolder
{
public:
    ResourceHolder(const std::string& name) : resourceName(name)
    {
        std::cout << "[CONSTRUCT] ResourceHolder '" << resourceName << "' created\n";
    }

    ~ResourceHolder() noexcept
    {
        std::cout << "[DESTROY] ResourceHolder '" << resourceName << "' destroyed (stack unwinding)\n";
    }

private:
    std::string resourceName;
};

// ===========================================================
// Functie care demonstreaza stack unwinding cu multiple catch
// ===========================================================
void demonstrateExceptionHandling()
{
    std::cout << "\n========== CERINTA 1: Exception Handling Demo ==========\n";

    // Test 1: InvalidCoordinateException cu stack unwinding
    std::cout << "\n[TEST 1] InvalidCoordinateException with stack unwinding:\n";
    try
    {
        ResourceHolder res1("Resource1");
        std::cout << "Attempting to create Point with invalid coordinate (NaN)...\n";
        
        // Acest constructor va arunca InvalidCoordinateException
        Point invalid(NAN, 5.0f);
    }
    catch (const InvalidCoordinateException& e)
    {
        // Catch pentru excepție derivată mai întâi (CERINTA 1)
        std::cout << "[CAUGHT] InvalidCoordinateException: " << e.what() << "\n";
        std::cout << "         Details: " << e.getDetails() << "\n";
        std::cout << "         Error Code: " << e.getErrorCode() << "\n";
    }
    catch (const ShapeException& e)
    {
        // Catch pentru clasa de bază (CERINTA 1)
        std::cout << "[CAUGHT] ShapeException: " << e.what() << "\n";
    }
    catch (const std::runtime_error& e)
    {
        // Catch pentru std::runtime_error (CERINTA 1)
        std::cout << "[CAUGHT] std::runtime_error: " << e.what() << "\n";
    }
    catch (...)
    {
        // Catch all ca ultim resort (CERINTA 1)
        std::cout << "[CAUGHT] Unknown exception\n";
    }

    // Test 2: setCoord cu InvalidCoordinateException
    std::cout << "\n[TEST 2] setCoord with InvalidCoordinateException:\n";
    try
    {
        ResourceHolder res2("Resource2");
        Point validPoint(3.0f, 4.0f);
        std::cout << "Valid point created: " << validPoint << "\n";
        
        std::cout << "Attempting to set invalid Y coordinate (Infinity)...\n";
        validPoint.setCoord(1.0f, INFINITY);
    }
    catch (const InvalidCoordinateException& e)
    {
        std::cout << "[CAUGHT] InvalidCoordinateException: " << e.what() << "\n";
        std::cout << "         Coordinate index: " << e.getCoordinateIndex() << " (0=X, 1=Y)\n";
    }
    catch (const ShapeException& e)
    {
        std::cout << "[CAUGHT] ShapeException: " << e.what() << "\n";
    }
    catch (...)
    {
        std::cout << "[CAUGHT] Unknown exception\n";
    }

    // Test 3: CapacityException demo
    std::cout << "\n[TEST 3] CapacityException demo:\n";
    try
    {
        ResourceHolder res3("Resource3");
        // Simulează o depășire de capacitate
        throw CapacityException(100, 150, 42, "ShapeManager capacity exceeded");
    }
    catch (const InvalidCoordinateException& e)
    {
        std::cout << "[CAUGHT] InvalidCoordinateException: " << e.what() << "\n";
    }
    catch (const CapacityException& e)
    {
        std::cout << "[CAUGHT] CapacityException: " << e.what() << "\n";
        std::cout << "         Capacity: " << e.getCurrentCapacity() << "\n";
        std::cout << "         Requested: " << e.getRequestedSize() << "\n";
        std::cout << "         Affected ID: " << e.getAffectedId() << "\n";
    }
    catch (const ShapeException& e)
    {
        std::cout << "[CAUGHT] ShapeException: " << e.what() << "\n";
    }
    catch (...)
    {
        std::cout << "[CAUGHT] Unknown exception\n";
    }

    std::cout << "\n===== End of Exception Handling Demo =====\n\n";
}

int main()
{
    // CERINTA 1: Demonstrare Exception Handling
    try
    {
        demonstrateExceptionHandling();

        // CERINTA 3: STL Containers & Algorithms Demo
        ShapeRepository repo;
        repo.demonstrateCRUD();
        repo.demonstrateAlgorithms();

        // Continuă cu aplicația normală
        ShapeManager *sm = new ShapeManager("My Shapes");
        PageManager::setSM(sm);

        PageManager::changePage(PageManager::getPage("mainPage"));

        delete sm;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Unexpected exception in main: " << e.what() << "\n";
        return 1;
    }
    catch (...)
    {
        std::cerr << "Unknown exception in main\n";
        return 1;
    }

    return 0;
}