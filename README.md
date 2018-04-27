# MachineLearningCS170

Data set information:
https://archive.ics.uci.edu/ml/datasets/Fertility

Must compile with C++11

Example of input and output:
$ ./a.out                                                                                                     
Welcome to Luis Lopez's Feature Selection Algorithm.                                                          
Type in the name of the file to test: 72.txt    
                                                                                                                                                                          
Type the number of the algorithm you want to run.                                                                                                                                                                                       
1) Forward Selection                                                                                          
2) Backward Elimination                                                                                       
3) Luis's Special Algorithm 
                                                                                                                                                                                                                        
1
This dataset has 10 features (not including the class attribute), with 100 instances.   

Please wait while I normalize the data... Done!                                                                                                                                                                             

Beginning search                                                                                                                                                                                                                    

Using features(s) {1} accuracy is 69%                                                                         
Using features(s) {2} accuracy is 74%                                                                         
Using features(s) {3} accuracy is 74%                                                                         
Using features(s) {4} accuracy is 69%                                                                         
Using features(s) {5} accuracy is 65%                                                                         
Using features(s) {6} accuracy is 82%                                                                         
Using features(s) {7} accuracy is 65%                                                                        
Using features(s) {8} accuracy is 75%                                                                         
Using features(s) {9} accuracy is 73%                                                                         
Using features(s) {10} accuracy is 68%                                                                                                                                                                              

Feature set {6} was best, accuracy is 82%                                                                                                                                                                                           
Using features(s) {6,1} accuracy is 80%                                                                       
Using features(s) {6,2} accuracy is 98%                                                                       
Using features(s) {6,3} accuracy is 88%                                                                       
Using features(s) {6,4} accuracy is 85%                                                                       
Using features(s) {6,5} accuracy is 84%                                                                       
Using features(s) {6,7} accuracy is 86%                                                                       
Using features(s) {6,8} accuracy is 82%                                                                       
Using features(s) {6,9} accuracy is 82%                                                                       
Using features(s) {6,10} accuracy is 87%                                                                                                                                                                            

Feature set {6,2} was best, accuracy is 98%                                                                                                                                                                                         
Using features(s) {6,2,1} accuracy is 97%                                                                     
Using features(s) {6,2,3} accuracy is 92%                                                                     
Using features(s) {6,2,4} accuracy is 95%                                                                     
Using features(s) {6,2,5} accuracy is 91%                                                                     
Using features(s) {6,2,7} accuracy is 94%                                                                     
Using features(s) {6,2,8} accuracy is 96%                                                                     
Using features(s) {6,2,9} accuracy is 97%                                                                    
Using features(s) {6,2,10} accuracy is 95%                                                                                                                                                                          

(Warning, Accuracy has decreased! Continuing search in case of local maxima)                                  
Feature set {6,2,1} was best, accuracy is 97%                                                                                                                                                                                       

Using features(s) {6,2,1,3} accuracy is 88%                                                                   
Using features(s) {6,2,1,4} accuracy is 87%                                                                   
Using features(s) {6,2,1,5} accuracy is 90%                                                                  
Using features(s) {6,2,1,7} accuracy is 88%                                                                   
Using features(s) {6,2,1,8} accuracy is 91%                                                                   
Using features(s) {6,2,1,9} accuracy is 95%                                                                   
Using features(s) {6,2,1,10} accuracy is 89%                                                                                                                                                                        

(Warning, Accuracy has decreased! Continuing search in case of local maxima)                                  
Feature set {6,2,1,9} was best, accuracy is 95%                                                                                                                                                                                     

Using features(s) {6,2,1,9,3} accuracy is 93%                                                                 
Using features(s) {6,2,1,9,4} accuracy is 89%                                                                 
Using features(s) {6,2,1,9,5} accuracy is 86%                                                                 
Using features(s) {6,2,1,9,7} accuracy is 88%                                                                 
Using features(s) {6,2,1,9,8} accuracy is 89%                                                                 
Using features(s) {6,2,1,9,10} accuracy is 94%                                                                                                                                                                      

(Warning, Accuracy has decreased! Continuing search in case of local maxima)                                  
Feature set {6,2,1,9,10} was best, accuracy is 94%                                                                                                                                                                                  

Using features(s) {6,2,1,9,10,3} accuracy is 86%                                                              
Using features(s) {6,2,1,9,10,4} accuracy is 88%                                                              
Using features(s) {6,2,1,9,10,5} accuracy is 87%                                                              
Using features(s) {6,2,1,9,10,7} accuracy is 84%                                                              
Using features(s) {6,2,1,9,10,8} accuracy is 83%                                                                                                                                                                    

(Warning, Accuracy has decreased! Continuing search in case of local maxima)                                  
Feature set {6,2,1,9,10,4} was best, accuracy is 88%                                                                                                                                                                                

Using features(s) {6,2,1,9,10,4,3} accuracy is 84%                                                            
Using features(s) {6,2,1,9,10,4,5} accuracy is 85%                                                            
Using features(s) {6,2,1,9,10,4,7} accuracy is 82%                                                            
Using features(s) {6,2,1,9,10,4,8} accuracy is 87%                                                                                                                                                                  

(Warning, Accuracy has decreased! Continuing search in case of local maxima)                                  
Feature set {6,2,1,9,10,4,8} was best, accuracy is 87%                                                                                                                                                                              

Using features(s) {6,2,1,9,10,4,8,3} accuracy is 76%                                                          
Using features(s) {6,2,1,9,10,4,8,5} accuracy is 87%                                                          
Using features(s) {6,2,1,9,10,4,8,7} accuracy is 78%                                                                                                                                                                

(Warning, Accuracy has decreased! Continuing search in case of local maxima)                                  
Feature set {6,2,1,9,10,4,8,5} was best, accuracy is 87%                                                                                                                                                                            

Using features(s) {6,2,1,9,10,4,8,5,3} accuracy is 74%                                                        
Using features(s) {6,2,1,9,10,4,8,5,7} accuracy is 79%                                                                                                                                                              

(Warning, Accuracy has decreased! Continuing search in case of local maxima)                                  
Feature set {6,2,1,9,10,4,8,5,7} was best, accuracy is 79%                                                                                                                                                                          

Using features(s) {6,2,1,9,10,4,8,5,7,3} accuracy is 73%                                                                                                                                                            

(Warning, Accuracy has decreased! Continuing search in case of local maxima)                                  
Feature set {6,2,1,9,10,4,8,5,7,3} was best, accuracy is 73%    
                                                                                                                                                            
Finished search! The best feature subset is {6,2} which has an accuracy of 98%  
