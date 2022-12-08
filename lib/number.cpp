#include "number.h"

#include <cmath>



uint2022_t from_uint(uint32_t i) {
    
    uint2022_t n;

    // Two situations because uint32_t max value (2^32) > 10^9
    // but 2^32 < 10^18
    if (i < mod) {
        n.arr[0] = i;
        n.length = 1;
    }

    else {
        n.arr[0] = i % mod;
        n.arr[1] = i / mod;
        n.length = 2;
    }
    return n;
}

uint2022_t from_string(const char* buff) {
    
    // General structure of struct uint2022_t:
    // 
    // We have array arr of uint32_t where is every element strore 9(nine) digits
    // of this number (in decimal(desyatichnaya) number system.
    // Besides first 9 digits (start from young digit) store in arr[0] (with saving the order)
    // second 9 gigits in arr[1] 
    // third 9 digits in arr[2]
    // ...
    // in last uint32_t may stroe less than 9 digits
    // 
    // example:
    // 12345678901234567890
    // 
    // arr[0] = 234567890
    // arr[1] = 345678901
    // arr[2] = 12
    //


    // Check for overflowing

    uint2022_t n;

    uint64_t sum = 0;
    int size = 0;
    int c = 0; // Universal counter
    int ind = 0;
    int pwr = 0;

    // Find size of buff
    while (buff[c] != '\0') {
        ++size;
        ++c;
    }

    // All obviosly
    if (size > 0) {

        // Find n.length of n
        if (size % 9 == 0) { n.length = size / 9; }
        else { n.length = (size / 9) + 1; }


        if (n.length < 64 + 1) {

            // Revers
            char* buff_revers = new char[size];

            for (int i = 0; i < size; ++i) {
                buff_revers[i] = buff[size - 1 - i];
            }

            // We will take 9 chars from buff and make abcdefghi number(9 digits)
            for (int i = 0; i < n.length; ++i) {

                pwr = 0;
                sum = 0;

                if (size >= 9) {
                    for (int j = 0; j < 9; ++j) {
                        sum += (buff_revers[ind] - 48) * pow(10, pwr);
                        ++ind;
                        ++pwr;
                    }

                    if (n.arr[i] + sum > mod - 1) {
                        n.arr[i] = (sum + n.arr[i]) % mod;
                        n.arr[i + 1] += 1;
                        // We can add 1 beacause in this moment n.arr[i + 1] was = 0
                        // that less than 1000000000 - 1;
                    }

                    else {
                        n.arr[i] = sum + n.arr[i];
                    }

                    size -= 9;
                }

                else {
                    for (int j = 0; j < size; ++j) {
                        sum += (buff_revers[ind] - 48) * pow(10, pwr);
                        ++ind;
                        ++pwr;
                    }

                    if (n.arr[i] + sum > mod - 1) {
                        n.arr[i] = (sum + n.arr[i]) % mod;
                        n.arr[i + 1] += 1;
                        // We can add 1 beacause in this moment n.arr[i + 1] was = 0
                        // that less than 1000000000 - 1;
                    }

                    else {
                        n.arr[i] = sum + n.arr[i];
                    }

                    size -= size;
                }
            }

            //delete[] buff_revers;

            return n;
        }

        else {
            std::cout << "Undefined behavior" << '\n';
            exit(0);
        }
    }

    else {
        std::cout << "Undefined beahvior" << '\n';
        exit(0);
    }
}

uint2022_t operator+(const uint2022_t& lhs, const uint2022_t& rhs) {

    const int max_int_amount = std::max(lhs.length, rhs.length);
    int length_new = 0;
    uint2022_t n;

    for (int i = 0; i < max_int_amount; ++i) {

        // Checking for overflowing in 9 digits
        if (lhs.arr[i] + rhs.arr[i] + n.arr[i] > mod - 1) {

            // Cheking for existance of cell with i + 1 index
            if (i + 1 < 64) {
                n.arr[i] = (lhs.arr[i] + rhs.arr[i] + n.arr[i]) % mod;
                n.arr[i + 1] += 1;
            }

            else {
                std::cout << "Undefined behavior" << '\n';
                exit(0);
            }
        }

        else {
            n.arr[i] = lhs.arr[i] + rhs.arr[i] + n.arr[i];
        }   
    }

    length_new = 1;

    // finding length of n
    for (int i = 63; i > -1; --i) {
        if (n.arr[i] != 0) {
            length_new = i + 1;
            break;
        }
    }
    
    n.length = length_new;

    return n;
}

uint2022_t operator-(const uint2022_t& lhs, const uint2022_t& rhs) {
    
    const int max_int_amount = std::max(lhs.length, rhs.length);
    int length_new = 0;
    int minus_one = 0;
    uint2022_t n;

    for (int i = 0; i < max_int_amount; ++i) {
        if (lhs.arr[i] < rhs.arr[i] + minus_one) {
            
            // Checking for existance of cell with i + 1 index
            if (i + 1 < 64) {
                
                // Checking for 
                if (lhs.arr[i + 1] > 0) {
                    n.arr[i] = mod + lhs.arr[i] - rhs.arr[i] - minus_one;
                    minus_one = 1;
                }

                else {
                    std::cout << "Udefined behaviur";
                    exit(0);
                }
            }

            else {
                std::cout << "Undefined beahviur";
                exit(0);
            }
        }

        else {
            n.arr[i] = lhs.arr[i] - rhs.arr[i] - minus_one;
            minus_one = 0;
        }
    }

    length_new = 1;

    // Finding length of n
    for (int i = 63; i > -1; --i) {
        if (n.arr[i] != 0) {
            length_new = i + 1;
            break;
        }
    }

    n.length = length_new;
    
    return n;
}

uint2022_t operator*(const uint2022_t& lhs, const uint2022_t& rhs) {

    uint2022_t n;

    const int max_int_amount = std::max(lhs.length, rhs.length);
    const int lhs_int_length = lhs.length;
    const int rhs_int_length = rhs.length;
    int length_new = 0;
    uint64_t temp = 0;

    for (int i = 0; i < lhs_int_length; ++i) {
        for (int j = 0; j < rhs_int_length; ++j) {
            temp = (uint64_t)lhs.arr[i] * (uint64_t)rhs.arr[j];
            
            // Checking for overflowing in 9 digits
            if (n.arr[i + j] + (uint32_t)(temp % mod) > mod - 1) {
                
                // Cheking for existance of cell with i + 1 index
                if (i + j + 1 < 64) {
                    n.arr[i + j] = (n.arr[i+j] + (uint32_t)(temp % mod)) % mod;
                    n.arr[i + j + 1] += 1;
                }

                else {
                    std::cout << "Undefined behavior";
                    exit(0);
                }
            }

            // If its not overflowing in 9 gigits)
            else {
                n.arr[i + j] += (uint32_t)(temp % mod);
            }

            // Checking for overflowing in 9 digits
            if (n.arr[i + j + 1] + (uint32_t)(temp / mod) > mod - 1) {
                
                // Cheking for existance of cell with i + 1 index
                if (i + j + 1 + 1 < 64) {
                    n.arr[i + j + 1] = (n.arr[i + j + 1] + (uint32_t)(temp / mod)) % mod;
                    n.arr[i + j + 1 + 1] += 1;
                }

                else {
                    std::cout << "Undefined behavior";
                    exit(0);
                }
            }

            // If its not overflowing in 9 gigits)
            else {
                n.arr[i + j + 1] += (uint32_t)(temp / mod);
            }
        }
    }

    // Cheking every uint32_t for exeeds(prevyshatq) 1000000000 - 1 value
    for (int i = 0; i < 64; ++i) {
        if (n.arr[i] > mod - 1) {
            if (i + 1 < 64) {
                n.arr[i] = n.arr[i] % mod;
                n.arr[i + 1] += 1; 
                // We can add just 1(one), not n.arr[i] % 1 * 10^9
                // beacuse we have not so much +1 operations to n.arr[i]
                // that n.arr[i] beacame > 2 * 10^9
            }
            else {
                std::cout << "Undefined behavior";
                exit(0);
            }
        }
    }

    length_new = 1;

    for (int i = 63; i > -1; --i) {
        if (n.arr[i] != 0) {
            length_new = i + 1;
            break;
        }
    }

    n.length = length_new;

    return n;
}

uint2022_t operator/(const uint2022_t& lhs, const uint2022_t& rhs) {
    return uint2022_t();
}

bool operator==(const uint2022_t& lhs, const uint2022_t& rhs) {
    for (int i = 0; i < 64; ++i) {
        if (lhs.arr[i] != rhs.arr[i]) {
            return false;
        }
    }
    return true;
}

bool operator!=(const uint2022_t& lhs, const uint2022_t& rhs) {
    return !(lhs==rhs);
}

std::ostream& operator<<(std::ostream& stream, const uint2022_t& value) {
    
    int c = 0; // Universal counter (amount of digits in last uint32_t)
    int temp = 0;
    int temp2 = 0;

    // Finding amount of digits in last unit32_t
    temp = value.arr[value.length - 1];

    if (temp == 0) { c = 1; }

    while (temp > 0){
        temp = temp / 10;
        ++c;
    }

    // Convert all(expect last) uint32_t in one c_style string
    char* buff = new char[c + (value.length - 1) * 9];

    for (int i = 0; i < value.length - 1; ++i) {
        
        temp2 = value.arr[i];

        for (int j = 0; j < 9; ++j) {
            buff[i * 9 + j] = temp2 % 10 + 48;
            temp2 = temp2 / 10;
        }
    }

    // Add converted last uint32_t in our c-style string
    temp2 = value.arr[value.length - 1];
    for (int j = 0; j < c; ++j) {
        buff[(value.length - 1) * 9 + j] = temp2 % 10 + 48;
        temp2 = temp2 / 10;
    }

    // Revers buff
    char* buff_revers = new char[(c + (value.length - 1) * 9) + 1]; // +1 for \0 symbol

    for (int i = 0; i < (c + (value.length - 1) * 9); ++i) {
        buff_revers[i] = buff[(c + (value.length - 1) * 9) - 1 - i];
    }

    buff_revers[(c + (value.length - 1) * 9)] = '\0';

    return stream << buff_revers;
}
