#include <bits/stdc++.h>

using namespace std;

class DocElement{
    public:
        virtual void render() = 0;
        virtual ~DocElement() {}
};

class TextElement : public DocElement {
    public:
        string data;
        TextElement (string s){
            this->data = s;
        }
        void render() override {
            cout << "rendering text element..." << data << endl;
        }
};

class ImgElement : public DocElement {
    public:
        string data;
        ImgElement (string s){
            this->data = s;
        }
        void render() override {
            cout << "rendering image element..." << data << endl;
        }
};

class Documents {
    public:
        vector<DocElement*> docs;

        void addDoc(DocElement* doc){
            docs.push_back(doc);
            cout << "doc added.." << endl;
        }

        void removeDoc(){
            docs.pop_back();
            cout << "doc removed..." << endl; 
        }

        void render() {
            cout << "rendering..." << endl;
            for(auto &it: docs){
                it->render();
            }
        }
};

class Persistance {
    public:
        virtual void save() = 0;
        virtual ~Persistance() {}
};

class saveToMongoDB : public Persistance {
    public:
        void save() override{
            cout << "saved to mongodb." << endl;
        }
};

class saveToSQL : public Persistance {
    public:
        void save() override{
            cout << "saved to SQL." << endl;
        }
};

class DocEditor {
    private:
        Documents docs;
        Persistance *db;

    public:
        DocEditor(Persistance *db) {
            this->db = db;
        }
        void addDoc(DocElement *doc) {
            docs.addDoc(doc);
        }

        void removeDoc(){
            docs.removeDoc();
        }

        void render(){
            docs.render();
        }

        void save(){
            db->save();
        }
};

int main() {
    saveToMongoDB mongo;

    DocEditor editor(&mongo);

    TextElement text1("Hello World");
    ImgElement img1("image.png");

    editor.addDoc(&text1);
    editor.addDoc(&img1);
    editor.render();
    editor.save();
    editor.removeDoc();
    editor.render();

    return 0;
}