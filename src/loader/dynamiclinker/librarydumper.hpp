#ifndef LIBRARY_DUMPER_H
#define LIBRARY_DUMPER_H

class CLibrary;

class ILibraryDumper
{
public:
    virtual ~ILibraryDumper() = default;
    virtual void dump(CLibrary* library) = 0;
};

#endif