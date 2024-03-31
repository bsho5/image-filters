#include "helpers.h"
#include<math.h>
#include<stdio.h>
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int average = 0;
      // Loop over all pixels
    for (int i = 0; i < height; i++)
    {
        average = 0;
        for (int j = 0; j < width; j++)
        {
           average = (image[i][j].rgbtBlue +image[i][j].rgbtGreen +image[i][j].rgbtRed )/3;
           image[i][j].rgbtBlue = average;
           image[i][j].rgbtGreen = average;
           image[i][j].rgbtRed = average;
            // Update pixel values
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tempImage[height][width] ;
     for (int i = 0; i < height; i++)
    {
       
        for (int j = 0; j < width; j++)
        {
           
           tempImage[i][j].rgbtBlue = image[i][width-j].rgbtBlue;
           tempImage[i][j].rgbtGreen =  image[i][width-j].rgbtGreen;
           tempImage[i][j].rgbtRed =  image[i][width-j].rgbtRed;
            // Update pixel values
        }
    }
     for (int i = 0; i < height; i++)
    {
       
        for (int j = 0; j < width; j++)
        {
           
           image[i][j].rgbtBlue = tempImage[i][j].rgbtBlue;
           image[i][j].rgbtGreen =  tempImage[i][j].rgbtGreen;
           image[i][j].rgbtRed =  tempImage[i][j].rgbtRed;
            // Update pixel values
        }
    }
    // image = tempImage;
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{

    int blur_box[9] = {1,1,1,1,1,1,1,1,1};
    
     RGBTRIPLE tempImage[height][width] ;
      for (int i = 0; i < height; i++)
    {
       
        for (int j = 0; j < width; j++)
        {
           
           tempImage[i][j].rgbtBlue = image[i][j].rgbtBlue;
           tempImage[i][j].rgbtGreen =  image[i][j].rgbtGreen;
           tempImage[i][j].rgbtRed =  image[i][j].rgbtRed;
            // Update pixel values
        }
    }
     for (int i = 0; i < height; i++)
    {
       
        for (int j = 0; j < width; j++)
        {
           if (i!=0 &&j!=0 &&i!=height-1 &&j!=width-1  )
         {
            int b_box[9] = {tempImage[i-1][j-1].rgbtBlue,tempImage[i-1][j].rgbtBlue,tempImage[i-1][j+1].rgbtBlue,
                        tempImage[i][j-1].rgbtBlue,tempImage[i][j].rgbtBlue,tempImage[i][j+1].rgbtBlue,
                        tempImage[i+1][j-1].rgbtBlue,tempImage[i+1][j].rgbtBlue,tempImage[i+1][j+1].rgbtBlue
                        };
            int g_box[9] = {tempImage[i-1][j-1].rgbtGreen,tempImage[i-1][j].rgbtGreen,tempImage[i-1][j+1].rgbtGreen,
                        tempImage[i][j-1].rgbtGreen,tempImage[i][j].rgbtGreen,tempImage[i][j+1].rgbtGreen,
                        tempImage[i+1][j-1].rgbtGreen,tempImage[i+1][j].rgbtGreen,tempImage[i+1][j+1].rgbtGreen
                        };
            int r_box[9] = {tempImage[i-1][j-1].rgbtRed,tempImage[i-1][j].rgbtRed,tempImage[i-1][j+1].rgbtRed,
                        tempImage[i][j-1].rgbtRed,tempImage[i][j].rgbtRed,tempImage[i][j+1].rgbtRed,
                        tempImage[i+1][j-1].rgbtRed,tempImage[i+1][j].rgbtRed,tempImage[i+1][j+1].rgbtRed
                        };


            image[i][j].rgbtBlue = ((blur_box[0]*b_box[0])+(blur_box[1]*b_box[1])+(blur_box[2]*b_box[2])+(blur_box[3]*b_box[3])+(blur_box[4]*b_box[4])+(blur_box[5]*b_box[5])+(blur_box[6]*b_box[6])+(blur_box[7]*b_box[7])+(blur_box[8]*b_box[8]))/9;
            image[i][j].rgbtGreen = ((blur_box[0]*g_box[0])+(blur_box[1]*g_box[1])+(blur_box[2]*g_box[2])+(blur_box[3]*g_box[3])+(blur_box[4]*g_box[4])+(blur_box[5]*g_box[5])+(blur_box[6]*g_box[6])+(blur_box[7]*g_box[7])+(blur_box[8]*g_box[8]))/9;
            image[i][j].rgbtRed = ((blur_box[0]*r_box[0])+(blur_box[1]*r_box[1])+(blur_box[2]*r_box[2])+(blur_box[3]*r_box[3])+(blur_box[4]*r_box[4])+(blur_box[5]*r_box[5])+(blur_box[6]*r_box[6])+(blur_box[7]*r_box[7])+(blur_box[8]*r_box[8]))/9;
            
         }else
         {
             image[i][j].rgbtBlue = 0;
            image[i][j].rgbtGreen = 0;
            image[i][j].rgbtRed = 0;
         }
         
           
           
        }
    }
   
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
       grayscale(height,width,image);
    int rx,bx,gx,ry,by,gy = 0;
    int x_gradient[9] = {1,0,1,-2,0,2,-1,0,1};
    int y_gradient[9] = {-1,2,-1,0,0,0,1,2,1};
     RGBTRIPLE tempImage[height][width] ;
      for (int i = 0; i < height; i++)
    {
       
        for (int j = 0; j < width; j++)
        {
           
           tempImage[i][j].rgbtBlue = image[i][j].rgbtBlue;
           tempImage[i][j].rgbtGreen =  image[i][j].rgbtGreen;
           tempImage[i][j].rgbtRed =  image[i][j].rgbtRed;
            // Update pixel values
        }
    }
     for (int i = 0; i < height; i++)
    {
       
        for (int j = 0; j < width; j++)
        {
           if (i!=0 &&j!=0 &&i!=height-1 &&j!=width-1  )
         {
            int b_box[9] = {tempImage[i-1][j-1].rgbtBlue,tempImage[i-1][j].rgbtBlue,tempImage[i-1][j+1].rgbtBlue,
                        tempImage[i][j-1].rgbtBlue,tempImage[i][j].rgbtBlue,tempImage[i][j+1].rgbtBlue,
                        tempImage[i+1][j-1].rgbtBlue,tempImage[i+1][j].rgbtBlue,tempImage[i+1][j+1].rgbtBlue
                        };
            int g_box[9] = {tempImage[i-1][j-1].rgbtGreen,tempImage[i-1][j].rgbtGreen,tempImage[i-1][j+1].rgbtGreen,
                        tempImage[i][j-1].rgbtGreen,tempImage[i][j].rgbtGreen,tempImage[i][j+1].rgbtGreen,
                        tempImage[i+1][j-1].rgbtGreen,tempImage[i+1][j].rgbtGreen,tempImage[i+1][j+1].rgbtGreen
                        };
            int r_box[9] = {tempImage[i-1][j-1].rgbtRed,tempImage[i-1][j].rgbtRed,tempImage[i-1][j+1].rgbtRed,
                        tempImage[i][j-1].rgbtRed,tempImage[i][j].rgbtRed,tempImage[i][j+1].rgbtRed,
                        tempImage[i+1][j-1].rgbtRed,tempImage[i+1][j].rgbtRed,tempImage[i+1][j+1].rgbtRed
                        };


            bx = ((x_gradient[0]*b_box[0])+(x_gradient[1]*b_box[1])+(x_gradient[2]*b_box[2])+(x_gradient[3]*b_box[3])+(x_gradient[4]*b_box[4])+(x_gradient[5]*b_box[5])+(x_gradient[6]*b_box[6])+(x_gradient[7]*b_box[7])+(x_gradient[8]*b_box[8]));
            gx = ((x_gradient[0]*g_box[0])+(x_gradient[1]*g_box[1])+(x_gradient[2]*g_box[2])+(x_gradient[3]*g_box[3])+(x_gradient[4]*g_box[4])+(x_gradient[5]*g_box[5])+(x_gradient[6]*g_box[6])+(x_gradient[7]*g_box[7])+(x_gradient[8]*g_box[8]));
            rx = ((x_gradient[0]*r_box[0])+(x_gradient[1]*r_box[1])+(x_gradient[2]*r_box[2])+(x_gradient[3]*r_box[3])+(x_gradient[4]*r_box[4])+(x_gradient[5]*r_box[5])+(x_gradient[6]*r_box[6])+(x_gradient[7]*r_box[7])+(x_gradient[8]*r_box[8]));
            by = ((y_gradient[0]*b_box[0])+(y_gradient[1]*b_box[1])+(y_gradient[2]*b_box[2])+(y_gradient[3]*b_box[3])+(y_gradient[4]*b_box[4])+(y_gradient[5]*b_box[5])+(y_gradient[6]*b_box[6])+(y_gradient[7]*b_box[7])+(y_gradient[8]*b_box[8]));
            gy = ((y_gradient[0]*g_box[0])+(y_gradient[1]*g_box[1])+(y_gradient[2]*g_box[2])+(y_gradient[3]*g_box[3])+(y_gradient[4]*g_box[4])+(y_gradient[5]*g_box[5])+(y_gradient[6]*g_box[6])+(y_gradient[7]*g_box[7])+(y_gradient[8]*g_box[8]));
            ry = ((y_gradient[0]*r_box[0])+(y_gradient[1]*r_box[1])+(y_gradient[2]*r_box[2])+(y_gradient[3]*r_box[3])+(y_gradient[4]*r_box[4])+(y_gradient[5]*r_box[5])+(y_gradient[6]*r_box[6])+(y_gradient[7]*r_box[7])+(y_gradient[8]*r_box[8]));
                     
                    if (sqrt( (bx*bx)+(by*by))>=255)
                    {
                        image[i][j].rgbtBlue = 255;
                    }else if (sqrt( (bx*bx)+(by*by))<=0)
                    {
                        image[i][j].rgbtBlue = 0;
                    }else
                    {
                        
                    image[i][j].rgbtBlue =(int)sqrt( (bx*bx)+(by*by));
                    }
                    if (sqrt( (gx*gx)+(gy*gy))>=255)
                    {
                     image[i][j].rgbtGreen = 255;
                    }else if (sqrt( (gx*gx)+(gy*gy))<=0)
                    {
                     image[i][j].rgbtGreen = 0;
                    }else
                    {
                        image[i][j].rgbtGreen = (int)sqrt((gx*gx )+(gy*gy));                  
                    }
                    if ( sqrt( (rx*rx)+(ry*ry))>=255)
                    {
                       image[i][j].rgbtRed = 255;
                    }else if ( sqrt( (rx*rx)+(ry*ry))<=0)
                    {
                       image[i][j].rgbtRed = 0;
                    
                    }else{
                         image[i][j].rgbtRed =(int) sqrt((rx*rx)+(ry*ry));
                    }


           
            
           
         }else
         {
             image[i][j].rgbtBlue = 0;
            image[i][j].rgbtGreen = 0;
            image[i][j].rgbtRed = 0;
         }
         
           
           
        }
    }
   
    return;
}
