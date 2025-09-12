#include <iostream>
#include "Bad_Entity_Type.cpp"
#include "Good_Entity_Type.cpp"

int main()
{

    Necromancer n;
    Knight k1;
    Knight k2;
    Knight k3;
    Knight k4;

    k1.death();
    k2.death();
    while (true)
    {
        n.createSkeletons();
        std::cout << "Out of loop" << std::endl;
        // goto end_loop;
        n.printInfo();
        break;
    }
    // end_loop:;
}
//         if (Entity::getDeadBodyCount() > 0)
//         {
//             std::cout << "Choice" << std::endl;
//             std::cout << "1. Create skeletons" << std::endl;
//             std::cout << "0. Dont create skeletons" << std::endl;
//             int choice;
//             std::cout << "Choice: ";
//             std::cin >> choice;

//             std::cout << '\n'
//                       << '\n';

//             switch (choice)
//             {
//             case 0:
//                 std::cout << "No skeletons created";
//                 break;
//             case 1:
//                 n.createSkeletons();
//                 break;

//             default:
//                 std::cout << "No such choice";
//                 break;
//             }
//         }
//         std::cout << "Out of loop" << std::endl;
//         goto end_loop;
//     }
