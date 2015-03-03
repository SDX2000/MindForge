#include "mmloader.h"


MmNode MmLoader::load(QDir baseDir)
{
    MmNode root("Root");
    root.addChild("Child 1");
    root.getChild(0).addChild("Grand child 1.1");
    root.getChild(0).addChild("Grand child 1.2");
    root.getChild(0).addChild("Grand child 1.3");
    root.addChild("Child 2");
    root.addChild("Child 3");

    return root;
}
