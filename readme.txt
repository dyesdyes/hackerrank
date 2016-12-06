This github project is just a mix of code, not a particular project.

The name is hackerrank, after the website, as you will find the solution of some of the problems from hackerrank.

Note that the code of those solutions is definitely not something I tried to polish or anything, the point was just to solve the problem in the shortest amount of time.

In "hackerrank\hackerrank\Not hackerrank related", there are also some random classes about data structures or other things that were created to actually implement and understand the class (hashtable, AVL tree etc...). The code is probably a bit better than in the hackerrank solutions but still wouldn't be production ready. Those classes will be likely to have associated unit tests in TestProject.

About the solution, it's a VS2012 solution using 3 different projects:
- MainProject : just a main function. In general I code the hackerrank solution right in the main file, then transfer it to a separate file in SourceFilesProject once done as it makes it easier to transfer the code from VS2012 to hackerrank website.
- SourceFilesProject: this project contains all the source code
- TestProject: This one contains the associated unit tests, note that most of the time, the hackerrank solutions won't have unit tests, but the other non-related classes will probably do.