#include  "../include/textviewer.h"

void TTextViewer::Insert(PTText pText) {
    system("clear");
    int input;
    string str;
    do {
        pText->Print();

        cout << "\tYou are in Insert interface!\n";
        cout << "1. Press '1' to InsDownLine\n";
        cout << "2. Press '2' to InsDownSection\n";
        cout << "3. Press '3' to InsNextLine\n";
        cout << "4. Press '4' to InsNextSection\n";
        cout << "5. Press '5' to SetLine\n";
        cout << "6. Press '6' to GetLine\n";
    } while (input != 0 && input < 7);

        cout << "Please, choose: ";
        cin >> input;

        switch (input) {
            case 1: 
                cout << "Input stroke: ";
                cin >> str;
                pText->InsDownLine(str);
                break;
            case 2:
                cout << "Input stroke: ";
                cin >> str;
                pText->InsDownSection(str);
                break;
            case 3:
                cout << "Input stroke: ";
                cin >> str;
                pText->InsNextLine(str);
                break;
            case 4:
                cout << "Input stroke: ";
                cin >> str;
                pText->InsNextSection(str);
                break;
            case 5:
                cout << "Input stroke: ";
                cin >> str;
                pText->SetLine(str);
                break;
            case 6:
                cout << "Current stroke: '" << pText->GetLine() << "'";
                break;
            default:
                cout << "WRONG!";
        }

        system("clear");
}

void TTextViewer::Delete(PTText pText) {
    system("CLS");
    int input;

    while (1) {
        pText->Print();

        cout << "\tYou are in Delete interface!\n";
        cout << "1. Press '1' to DelDownLine\n";
        cout << "2. Press '2' to DelDownSection\n";
        cout << "3. Press '3' to DelNextLine\n";
        cout << "4. Press '4' to DelNextSection\n";
        cout << "5. Press '0' to escape";

        cin >> input;

        switch (input) {
            case 1: 
                cout << "Input stroke: ";
                pText->DelDownLine();
                break;
            case 2:
                cout << "Input stroke: ";
                pText->DelDownSection();
                break;
            case 3:
                cout << "Input stroke: ";
                pText->DelNextLine();
                break;
            case 4:
                cout << "Input stroke: ";
                pText->DelNextSection();
                break;
            case 0:
                break;
            default:
                cout << "Wrong format";
        }

        system("pause");
        system("CLS");
        if (input == 0)
            break;
    }
}

void TTextViewer::Navigation(PTText pText) {
system("CLS");
    int input;

    while (1) {
        pText->Print();

        cout << "\tYou are in Navigation interface!\n";
        cout << "1. Press '1' to GoFirstLink\n";
        cout << "2. Press '2' to GoDownLink\n";
        cout << "3. Press '3' to GoNextLink\n";
        cout << "4. Press '4' to GoPrevLink\n";
        cout << "5. Press '0' to escape";

        cin >> input;

        switch (input) {
            case 1: 
                cout << "Input stroke: ";
                pText->GoFirstLink();
                break;
            case 2:
                cout << "Input stroke: ";
                pText->GoDownLink();
                break;
            case 3:
                cout << "Input stroke: ";
                pText->GoNextLink();
                break;
            case 4:
                cout << "Input stroke: ";
                pText->GoPrevLink();
                break;
            case 0:
                break;
            default:
                cout << "Wrong format";
        }

        system("pause");
        system("CLS");
        if (input == 0)
            break;
    }
}

void TTextViewer::Interface(PTText pText) {
    int input;

    while (1) {
        pText->Print();

        cout << "Privet\n";
        cout << "1. Press '1' to insert stroke\n";
        cout << "2. Press '2' to delete stroke\n";
        cout << "3. Press '3' to navigate in text\n";
        cout << "4. Press '4' to print text in console\n";
        cout << "5. Press '5' to print text in file\n";
        cout << "6. Press '6' to get text from file\n";
        cout << "7. Press '0' to close program\n\n";

        cout << "Please, choose: ";
        cin >> input;

        if (input == 1)
            Insert(pText);
        else if (input == 2)
            Delete(pText);
        else if (input == 3)
            Navigation(pText);
        else if (input == 4)
            pText->Print();
        else if (input == 5)
            pText->Write((char*)"out.txt");
        else if (input == 6)
            pText->Read((char*)"in.txt");
        else if (input == 0)
            break;
        else
            cout << "Input right";

        system("pause");
        system("CLS");        
    }
}