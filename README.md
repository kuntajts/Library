Library
=======

Intro To Data Structures Final

CS220 – Term Project: Maintaining an Inventory

Assigned: Thursday, October 31
Due: December 13th, last day of class
Submission: You must demonstrate the software to me, and in addition submit entire zipped Visual Studio project folder through Sakai.
Overview

Imagine that you have a part-time job at a local used bookstore.  Realizing that you know a good deal about computers, the store owner asks you to write an interactive program that will maintain the store's inventory of books that are for sale.

Objectives

Practice defining and implementing ADTs using interfaces
Practice choosing and using data structures
Practice with larger-scale OOP program design
Requirements

The inventory you are to create consists a list of book titles and the following information associated with each title:

Have value: number of copies of the book currently in stock
Want value: number of copies that should be in stock (when have value is less than want value, more copies are ordered).
Wait list: list of names of people who are waiting for this title (if it is sold out).
Because the owner plans to turn off the power to the computer when the store is closed, your inventory program will not be running at all times.  Therefore, the program must save the inventory to a file or files before execution terminates, and later restore the inventory from the file(s) when it is run again.

Input:
A file or files containing the previously saved inventory.
A file containing the information on an incoming shipment of books (see command D in following table).
Single letter commands – with arguments where necessary – that the user will enter interactively to inquire about or modify the inventory.
Output:
A file or files that contains the updated inventory. (Note that you remove from the inventory all items whose have values and want values are zero and whose wait lists are empty. Thus, these items do not appear in the file).
Output as specified by the individual commands.
 

Key Command

 
 
 
 
Provide a summary of all available commands.

I <title>

 
Display the information for a specified title.

 
 
List the information for the entire inventory (in alphabetical order by title)

A <title>

 
Add a book to the inventory. Prompt for initial want value. If the title already exists, inform the user and print the information for that title.

M <title>

 
Modify the want value for the specified title. Display current want value, and prompt user for new want value.

O <filename>

 
Create a purchase order for additional books based on a comparison of the have and want values in the inventory, so that the have value is brought up to the want value.

D <filename>

 
Take information from a delivery shipment of books, in a file.The file will contain the title and the count of each book shipped. Read the file, and update the "have" values in the inventory accordingly. Note that the program must add an item to the inventory if the delivered title is not present in the current inventory.

Finally, if there is a wait list for books delivered, the program should print the title of the book and the name of the person it should be put on hold for. The book should then be considered sold (the person should be removed from wait list, and the want value updated accordingly).

R <filename>

 
Write a return invoice to a file specifying books to be returned. This should bring the have value down to the want value for each book in the inventory.

S <title>

 
Decrease the count for the specified title by 1.If the title doesn't exist yet, it should be added. If the title is sold out (or didn't exist), prompt the user for the buyer's name and enter them on the wait list.

 
 
Save the inventory and wait lists in a file and terminate execution.

The problem as stated suggests, at a minimum, a set of operations for the inventory as a whole, and for individual inventory items.  These operations, along with any others you deem necessary at this level, specify and Abstract Data Type (ADT) and therefore should be defined by an interface class (a class containing no data and only pure virtual methods).  Your class, or classes, that manipulate either the inventory as a whole, or specific inventory items, should only reference these interface classes, and not the underlying data structures that implement them.  In this way, an alternate data structure could be used in the future to improve the program functionality, without editing the code that utilizes these ADTs.

An external class should control the interaction with the user, and perform operations on the inventory ADT or the inventory item ADT.  The inventory ADT and inventory item ADT should not communicate directly with the user.

 

Operations for the overall inventory ADT include:

List the inventory alphabetically (L command).
Get the inventory item associated with a title (I, M, D, O and S commands).
Modify/replace the inventory item associated with a title (M, D, R, and S commands).
Insert new inventory items (A and D commands).
Save the current inventory items when program execution terminates (Q command).
Restore the current inventory items when program execution begins again.
Operations for the inventory item ADT include:

get / set the "title" of the item.
get / set the "have" value of the item.
get/set the "want" value of the item.
Add new people to the end of the wait list (S command when item is sold out).
Delete people from the beginning of the wait list (D command when matching titles are delivered).
get the names on the wait list for a particular title (I and L commands).
Additional Requirements

Capitalization, spacing, and punctuation should not matter when accessing an item. In other words, "Leaves of Grass" and "Leaves-Of       Grass", and "leavesofgrass" should all access the same item. The item should maintain the formatting of the name as originally specified when entered.
The program must have error handling, meaning it should not crash due to user error. Appropriate error messages should be displayed to the user when errors occur, and program should continue execution.
Your solution must be object-oriented.  The project must be logically broken down into classes.  Data attributes must be private.
Memory must be handled appropriately:
The program should maintain a small memory footprint. Therefore, it should not be assumed that more than 5 entries exist at startup, and size should update accordingly.  
Memory must be allocated correctly and released at an appropriate time. This requires destructor methods and copy constructor methods wherever necessary (objects should be able to be passed by value and still maintain functionality).
You must use either linked lists or dynamic arrays that you create and maintain.  You cannot use any higher-level imported container classes, such as stl::Vector or stl::List.
Style

Please see the updated Style Guide, specifically the section on commenting.  Make sure that all your code is styled and commented correctly according to the Style Guide.
