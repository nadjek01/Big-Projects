if (not root->hasSubDir() or root->hasFiles()) {
        // cerr << "in base case" << endl;
        if (root->hasFiles()) {
            for (int i = 0; i < root->numFiles(); i++) {
                cout << dir_print + "/" + root->getFile(i) << endl;
                //cerr << "1" << endl;
            }
        }
    }