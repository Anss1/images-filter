#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include "bmplib.cpp"

#define f2(y,z) for(int i=0;i < y;i++)for(int j=0;j < z;j++)
#define f1(y) for(int i=0;i < y;i++)


using namespace std;

unsigned char image[SIZE][SIZE];  //global variable................
unsigned char image2[SIZE][SIZE];  //global variable................

void load_image ()
{
    char imageFileName[100];

    cout<<"Please enter file name of the image to process : ";
    cin.getline(imageFileName,100) ;

    strcat (imageFileName, ".bmp");
    readGSBMP(imageFileName, image);
}
void save_image ()
{
    char imageFileName[100];
    cout << "Please enter file name of the image to save : ";
    cin.ignore();
    cin.getline(imageFileName,100) ;
    system("cls");
    strcat (imageFileName, ".bmp");
    writeGSBMP(imageFileName, image2);
}


void B_and_W ()
{
    long int sum=0;
    double avg;
    f2(256,256)
    {
        sum+=image[i][j];
    }
    avg=sum/65536;
    f2(256,256)
    {
        if(image[i][j] > avg)
            image2[i][j]=255;
        else if(image[i][j] < avg)
            image2[i][j]=0;
    }

}

void invert_image ()
{
    f2(256,256)
    {
        if(image[i][j] == 0)
            image2[i][j]=255;
        else if(image[i][j] == 255)
            image2[i][j]=0;
        else
            image2[i][j]=255 - image[i][j];
    }
}
void merge_image ()
{
    char imageName[100];

    cout << "Please enter the name of image file to merge with : ";
    cin.ignore();
    cin.getline(imageName,100) ;
    system("cls");
    strcat (imageName, ".bmp");
    readGSBMP(imageName, image2);

    f2(256,256)
    {
        image2[i][j] = (image2[i][j]+image[i][j])/2;
    }

}

void flip_image (int ch)
{
    if(ch == 1)
    {
        //flip the image vertically..............................
        f2(256,256)
        {
            /*temp = image[i][j];
             image[i][j] = image[255-i][j];*/
            image2[255-i][j] = image[i][j];
        }
    }
    if(ch == 2)
    {
        //flip the image horizontally......................
        f2(256,256)
        {
            /*temp = image[i][j];
            image[i][j] = image[i][255-j];*/
            image2[i][255-j] = image[i][j];
        }
    }
}

void rotate_image (int ch)
{
    if(ch == 2)
    {
        //rotate 180 degree ...............................
        f2(256,256)
        {
            image2[i][j] = image[256-i][256-j];
        }
    }
    if(ch == 1)
    {
        //rotate 90 degree....................................
        f2(256,256)
        {
            image2[i][j] = image[256-j][i];
        }
    }
    if(ch == 3)
    {
        //rotate 270 degree....................................
        f2(256,256)
        {
            image2[i][j] = image[j][256-i];
        }
    }
}

void D_and_L (int ch)
{
    if(ch == 1)
    {
        //darken 50% ......................................
        f2(256,256)
        {
            image2[i][j] = image[i][j] * 0.5;
        }
    }
    if(ch == 2)
    {
        //lighten 50% ...............................
        f2(256,256)
        {
            image2[i][j] = 128 + image[i][j]*0.5;
        }
    }
}

void edge_detecting ()
{
    B_and_W ();
    for(int i = 0; i < 256; i++)
    {
        for(int j = 0; j < 255; j++)
        {
            if(image2[i][j] == 0)
            {
                for(int k = j+2; image2[i][k+1] < 255 && image2[i+1][k] < 255 && image2[i+1][k+1] < 255 && image2[i+1][k-1] < 255 && k < 255; k++)
                {
                    image2[i][k] = 255;
                }

            }

        }
    }
}

void  enlarge_Image(int sRow,int sCol)
{
    for(int i = 0,c = sRow; i < 256; i+=2,c++)
    {
        for(int j = 0, k = sCol; j < 256; j+=2,k++)
        {
            image2[i][j] = image[c][k];
            image2[i+1][j] = image[c][k];
            image2[i][j+1] = image[c][k];
            image2[i+1][j+1] = image[c][k];
        }
    }
}

void shrink_image (int ch)
{
    int w,h;
    if(ch == 1)
    {
        w = 2;
        h = 2;
    }

    if(ch == 2)
    {
        w = 4;
        h = 4;
    }

    if(ch == 3)
    {
        w = 3;
        h = 3;
    }

    for(int i=0,z=0; i<256 ; z++, i+=w)
    {
        for(int j=0,k=0; j<256 ; k++, j+=h)
        {
            image2[z][k] = image[i][j];
        }
    }
}

void mirror_image (int k)
{
    if(k == 1)
    {
        // first half..................................
        f2(256,128)
        {
            image2[i][j] = image[i][j];
        }
        f2(256,256)
        {
            image2[i][255-j] = image2[i][j];
        }
    }
    if(k == 3)
    {
        //upper half...............................................
        f2(128,256)
        {
            image2[i][j] = image[i][j];
        }
        f2(256,256)
        {
            image2[255-i][j] = image2[i][j];
        }
    }
    if(k == 4)
    {
        //lower half...............................................
        for(int i=128; i<256; i++)
        {
            for(int j=0; j<256; j++)
            {
                image2[i][j] = image[i][j];
            }
        }
        f2(256,256)
        {
            image2[i][j] = image2[255-i][j];
        }
    }
    if(k == 2)
    {
        //second half...................................................
        for(int i=0; i<256; i++)
        {
            for(int j=128; j<256; j++)
            {
                image2[i][j] = image[i][j];
            }
        }
        f2(256,256)
        {
            image2[i][j] = image2[i][255-j];
        }
    }
}

void shuffle_image()
{
    int numq[4];
    cout<<"Please enter your shuffle number's from 1 to 4 : ";
    for(int i=0; i<4; i++)
        cin>>numq[i];
    system("cls");
    int r[] = {0,0,128,128},c[] = {0,128,0,128},lr[] = {128,128,256,256},lc[] = {128,256,128,256};
    for(int n=0; n<4; n++)
    {
        for(int i=r[n],qr=r[numq[n]-1]; qr<lr[numq[n]-1] && i<lr[n]; qr++, i++)
        {
            for(int j=c[n],qc=c[numq[n]-1]; qc<lc[numq[n]-1] && j<lc[n]; qc++, j++)
            {
                image2[i][j] = image[qr][qc];
            }
        }
    }
}

void blur_image ()
{
    ;
    int avg=0,sum=0,temp[3][3]= {1,2,1,
                                 2,4,2,
                                 1,2,1};

    for(int r=3; r<256; r+=3)
    {
        for(int c=3; c<256; c+=3)
        {
            for(int sr=r-3, c1=0; sr<r; c1++, sr+=1)
            {
                for(int sc=c-3,c2=0; sc<c; c2++, sc+=1)
                {
                    sum+=(image[sr][sc]*temp[c1][c2]);
                }
            }
            avg = sum/16;
            sum = 0;

            for(int er=r-3; er<=r; er+=1)
            {
                for(int ec=c-3; ec<=c; ec+=1)
                {
                    image2[er][ec] = avg;
                }
            }
        }
    }


}

int main()
{
    char val;

    cout<<"Ahlan ya user ya habibi ;)\n\n";
    load_image ();
    system("cls");

    while(1)
    {
        cout<<"What do you want to do ?\n\n";
        cout<<"1- Black & White Filter.\n";
        cout<<"2- Invert Filter.\n";
        cout<<"3- Merge Filter.\n";
        cout<<"4- Flip Image.\n";
        cout<<"5- Rotate Image.\n";
        cout<<"6- Darken and Lighten Image.\n";
        cout<<"7- Detect Image Edges.\n";
        cout<<"8- Enlarge Image.\n";
        cout<<"9- Shrink Image.\n";
        cout<<"a- Mirror Image.\n";
        cout<<"b- Shuffle Image.\n";
        cout<<"c- Blur Image.\n";
        cout<<"s- Save the image to a file.\n";
        cout<<"0- Exit.\n\n\n";
        cout<<"Your choice is : ";
        cin>>val;
        system("cls");
        if(val=='1')
            B_and_W ();
        if(val=='2')
            invert_image ();
        if(val=='3')
            merge_image ();
        if(val=='4')
        {
            int choice;
            cout<<"1- To flip the image \" Vertically \".\n2- To flip the image \" Horizontally \".\n\nYour choice is : ";
            cin>>choice;
            system("cls");
            flip_image (choice);
        }

        if(val=='5')
        {
            int choice;
            cout<<"1- To rotate \" 90 \" degree.\n2- To rotate \" 180 \" degree.\n3- To rotate \" 270 \" degree.\n\nYour choice is : ";
            cin>>choice;
            system("cls");
            rotate_image (choice);
        }

        if(val=='6')
        {
            int choice;
            cout<<"1- To \" Darken \".\n2- To\" Lighten \".\n\nYour choice is : ";
            cin>>choice;
            system("cls");
            D_and_L (choice);
        }

        if(val=='7')
            edge_detecting ();
        if(val=='8')
        {
            int choice;
            cout<<"1- To enlarge \" first \" quarter.\n2- To enlarge \" Second \" quarter.\n3- To enlarge \" Third \" quarter.\n4- To enlarge \" Fourth \" quarter.\n\nYour choice is : ";
            cin>>choice;
            system("cls");
            if(choice == 1)
                enlarge_Image(0,0);
            if(choice == 2)
                enlarge_Image(0,127);
            if(choice == 3)
                enlarge_Image(127,0);
            if(choice == 4)
                enlarge_Image(127,127);
        }
        if(val=='9')
        {
            int choice;
            cout<<"1- To shrink to \" Half \".\n2- To shrink to \" Quarter \".\n3- To shrink to \" Third \".\n\nYour choice is : ";
            cin>>choice;
            system("cls");
            shrink_image (choice);
        }

        if(val=='s')
            save_image ();
        if(val == 'a')
        {
            int kind;
            cout<<"1- To mirror \" First \" half.\n2- To mirror \" Second \" half.\n3- To mirror \" Upper \" half.\n4- To mirror \" Lower \" half.\n\nYour choose is : ";
            cin>>kind;
            system("cls");
            mirror_image (kind);
        }

        if(val == 'b')
            shuffle_image();
        if(val == 'c')
            blur_image ();
        if(val=='0')
            break;
    }


    return 0;
}
