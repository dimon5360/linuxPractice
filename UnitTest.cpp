/**
 *  @file UnitTest.cpp
 *  @brief  Unit test class
 *
 *  @author Kalmykov Dmitry
 *
 *  @version 0.1
 *  @date 02.06.2020
 */

/* local headers */
#include "main.h"
#include "config.h"

/* user classes */
#include "UnitTest.hpp"
#include "SServer.hpp"
#include "DDatabase.hpp"

/* C++ std lib headers */
#include <memory>
#include <cstring>


using namespace boost::asio;

/* utils for unit test class ----------------------------------------------- */
/**
 * @brief Print unit tests result 
 */
void UUnitTest::PrintUnitTestErrorCode(void) {
    static std::string head = "Unit test result failed with error ";
    std::cout << head << boost::format("%u") % unitTestResult << std::endl;
}

/**
 * @brief Get unit test result 
 */
uint32_t UUnitTest::GetUnitTestResult(void) {
    return unitTestResult;
}

/* start of unit testing  -------------------------------------------------- */
void StartUnitTesting(void) {
    uint32_t errCode = ERR_OK;
    std::shared_ptr<UUnitTest> unittest = std::make_shared<UUnitTest>();

    // unit test for async print data to console
    // unittest->TestAsyncConsoleOutput();
    // if((errCode = unittest->GetUnitTestResult()) != ERR_OK) {
    //     unittest->PrintUnitTestErrorCode();            
    //     return;
    // }

    // unit test for basic class inheritance
    unittest->TestInheritBaseClass();
    if((errCode = unittest->GetUnitTestResult()) != ERR_OK) {
        unittest->PrintUnitTestErrorCode();            
        return;
    }

    // unit test for practise binary search tree using 
    unittest->TestBinarySearchTree();
    if((errCode = unittest->GetUnitTestResult()) != ERR_OK) {
        unittest->PrintUnitTestErrorCode();            
        return;
    }
    

    std::cout << "Unit testing result succed." << std::endl;
}

/* unit tests -------------------------------------------------------------- */

template <typename K>
struct KeyHash {
    uint32_t operator()(const K& key) const {
        // return reinterpret_cast<uint32_t>(key) % TABLE_SIZE;
        return key % 7;
    }
};

template <typename K, typename V>
class HashNode {

public:
    
    HashNode(const K &key, const V &value) :
        key(key), value(value), next(NULL) {

    }
    ~HashNode() {
        delete next;
    }


    K getKey() const {
        return key;
    }

    V getValue() const {
        return value;
    }

    void setValue(V value) {
        HashNode::value = value;
    }

    HashNode * getNext() const {
        return next;
    }

    void setNext(HashNode * next) {
        HashNode::next = next;
    }

private:
    K key;
    V value;
    HashNode * next; 

};


template <typename K, typename V, typename F = KeyHash<K>>
class HashMap {

public:

    HashMap() {
        table = new HashNode<K, V> *[7]();
    }

    ~HashMap() {
        for(size_t i = 0; i < 7; i++) {
            HashNode<K, V> *entry = table[i];
            while(entry != NULL) {
                HashNode<K, V> *prev = entry;
                entry = entry->getNext();
                delete prev;
            }
            table[i] = NULL;
        }
        delete [] table;
    }


    bool get(const K &key, V &value) {
        uint32_t hashValue = hashFunc(key);
        HashNode<K, V> *entry = table[hashValue];

        while(entry != NULL) {
            if(entry->getKey() == key) {
                value = entry->getValue();
                return true;
            }
            entry = entry->getNext();
        }
        return false;
    } 

    void put(const K &key, const V &value) {
        unsigned long hashValue = hashFunc(key);
        HashNode<K, V> *prev = NULL;
        HashNode<K, V> *entry = table[hashValue];

        while (entry != NULL && entry->getKey() != key) {
            prev = entry;
            entry = entry->getNext();
        }

        if (entry == NULL) {
            entry = new HashNode<K, V>(key, value);
            if (prev == NULL) {
                table[hashValue] = entry;
            } else {
                prev->setNext(entry);
            }
        } else {
            entry->setValue(value);
        }
    }

    void remove(const K &key) {
        unsigned long hashValue = hashFunc(key);
        HashNode<K, V> *prev = NULL;
        HashNode<K, V> *entry = table[hashValue];

        while (entry != NULL && entry->getKey() != key) {
            prev = entry;
            entry = entry->getNext();
        }

        if (entry == NULL) {
            return;
        }
        else {
            if (prev == NULL) {
                table[hashValue] = entry->getNext();
            } else {
                prev->setNext(entry->getNext());
            }
            delete entry;
        }
    }

private:

    HashNode<K, V> **table;
    F hashFunc;
};

void UUnitTest::TestBinarySearchTree(void) {

    using namespace std;

    struct MyKeyHash {
        unsigned long operator()(const int& k) const
        {
            return k % 10;
        }
    };

    HashMap<int, string, MyKeyHash> hmap;
    hmap.put(1, "val1");
    hmap.put(2, "val2");
    hmap.put(3, "val3");

    string value;
    hmap.get(2, value);
    cout << value << endl;
    bool res = hmap.get(3, value);
    if (res)
        cout << value << endl;
    hmap.remove(3);
    res = hmap.get(3, value);
    if (res)
        cout << value << endl;

    cout << "Test finished." << endl;

    unitTestResult = ERR_OK;
}


struct BaseClass {
public:
    BaseClass() {
        std::cout << "BaseClass()" << std::endl;
    }
    ~BaseClass() {
        std::cout << "~BaseClass()" << std::endl;
    }
};

struct DerivedClass: public BaseClass {
public:
    DerivedClass() {
        std::cout << "DerivedClass()" << std::endl;
    }

    ~DerivedClass() {
        std::cout << "~DerivedClass()" << std::endl;
    }
};

/**
 * @brief Unit test of inrheritance from base class
 */
void UUnitTest::TestInheritBaseClass(void) {
    
    using namespace std;

    cout << "Smart (shared) pointer to DerivedClass object A:" << endl;
    shared_ptr<DerivedClass> A = make_shared<DerivedClass>();
    cout << endl;
    
    cout << "Simple pointer to DerivedClass object B:" << endl;
    DerivedClass * B = new DerivedClass();
    delete B;
    cout << endl;

    cout << "Test finished." << endl;

    unitTestResult = ERR_OK;
}

// /**
//  * @brief Static function which must be called for async print data in console
//  */
// void AsyncOutData(const boost::system::error_code& /*e*/) {
//     std::cout << __func__ << "()" << std::endl;
// }

// void AsyncOutData0(const boost::system::error_code& /*e*/,
//     boost::asio::steady_timer* t, int* count) {
//     std::cout << __func__ << "()" << std::endl;
//     if (*count > 0)
//     {
//         std::cout << *count << std::endl;
//         --(*count);

//         t->expires_at(t->expiry() + boost::asio::chrono::seconds(1));
//         t->async_wait(boost::bind(AsyncOutData0,
//             boost::asio::placeholders::error, t, count));
//     }
// }

// void AsyncOutData1(const boost::system::error_code& /*e*/,
//     boost::asio::steady_timer* t, int* count) {
//     std::cout << __func__ << "()" << std::endl;
//     if (*count < 5)
//     {
//         std::cout << *count << std::endl;
//         ++(*count);

//         t->expires_at(t->expiry() + boost::asio::chrono::seconds(1));
//         t->async_wait(boost::bind(AsyncOutData1,
//             boost::asio::placeholders::error, t, count));
//     }
// }

// class printer {
// public:
//     /* default constructor */
//     // printer(boost::asio::io_context& io)
//     //     : timer_(io, boost::asio::chrono::seconds(1)),
//     //       count_(0) {
//     //         timer_.async_wait(boost::bind(&printer::print, this));
//     // }

//     /* overloaded constructor */
//     printer(boost::asio::io_context& io)
//         : strand_(boost::asio::make_strand(io)),
//           timer1_(io, boost::asio::chrono::seconds(1)),
//           timer2_(io, boost::asio::chrono::seconds(1)),

//           count_(0) {

//             timer1_.async_wait(boost::asio::bind_executor(strand_,
//             boost::bind(&printer::print1, this)));

//             timer2_.async_wait(boost::asio::bind_executor(strand_,
//             boost::bind(&printer::print2, this)));
//     }

//     ~printer() {
//         std::cout << "Final count is " << count_ << std::endl;
//     }

//     // void print() {
//     //     if(count_ < 5) {
//     //         std::cout << count_ << std::endl;
//     //         ++count_;
            
//     //         timer_.expires_at(timer_.expiry() + boost::asio::chrono::seconds(1));
//     //         timer_.async_wait(boost::bind(&printer::print, this));
//     //     }
//     // }

//     void print1()
//     {
//         if (count_ < 10)
//         {
//         std::cout << "Timer 1: " << count_ << std::endl;
//         ++count_;

//         timer1_.expires_at(timer1_.expiry() + boost::asio::chrono::seconds(1));

//         timer1_.async_wait(boost::asio::bind_executor(strand_,
//                 boost::bind(&printer::print1, this)));
//         }
//     }

//     void print2()
//     {
//         if (count_ < 10)
//         {
//         std::cout << "Timer 2: " << count_ << std::endl;
//         ++count_;

//         timer2_.expires_at(timer2_.expiry() + boost::asio::chrono::seconds(1));

//         timer2_.async_wait(boost::asio::bind_executor(strand_,
//                 boost::bind(&printer::print2, this)));
//         }
//     }

// private:
//     boost::asio::strand<boost::asio::io_context::executor_type> strand_;
//     boost::asio::steady_timer timer1_;
//     boost::asio::steady_timer timer2_;
//     // boost::asio::steady_timer timer_;
//     int count_;
// }; 

// /**
//  * @brief Unit test of asynchronous output data to console
//  */
// void UUnitTest::TestAsyncConsoleOutput(void) {
 
//     boost::asio::io_context io;

//     printer p(io);
    
//     boost::thread t(boost::bind(&boost::asio::io_context::run, &io));

//     io.run();

//     t.join();

//     std::cout << "Test finished." << std::endl;

//     unitTestResult = ERR_OK;
// }



