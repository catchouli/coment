#include <iostream>
#include <functional>
#include <clang-c/Index.h>

template <typename T>
T&& check(T&& x)
{
    if (!x)
    {
        fprintf(stderr, "Error\n");
        exit(1);
    }

    return std::move(x);
}

CXChildVisitResult drawtree(CXCursor cursor, CXCursor parent, CXClientData client_data)
{
    int depth = *(int*)client_data;
    int childDepth = depth + 1;

    // Draw tree stuff
    // Add spacing
    for (int i = 0; i < depth-1; ++i)
    {
        printf("  ");
    }

    // Add |-+ thing if this isn't the root node
    if (depth != 0)
    {
        printf("|-+ ");
    }

    // Write this component's name
    printf("%s\n", clang_getCString(clang_getCursorSpelling(cursor)));

    // Draw children
    clang_visitChildren(cursor, drawtree, &childDepth);

    // Continue traversal
    return CXChildVisit_Continue;
};

int main(int argc, char** argv)
{
    // Create index
    CXIndex idx = check(clang_createIndex(1, 1));

    // Create index action
    CXIndexAction idxAction = clang_IndexAction_create(idx);

    // Parse
    CXTranslationUnit tu;

    CXErrorCode ec = clang_parseTranslationUnit2(idx, "test.cpp", argv, argc,
        nullptr, 0, 0, &tu);
    
    // Traverse
    // Draw tree
    int depth = 0;

    drawtree(clang_getTranslationUnitCursor(tu), clang_getNullCursor(), &depth);

    CXType type = clang_getCursorType(clang_getTranslationUnitCursor(tu));

    system("pause");
}