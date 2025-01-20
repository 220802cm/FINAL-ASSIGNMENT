# -*- coding: utf-8 -*-
"""
Created on Tue Nov 26 08:27:20 2024

@author: 33631
"""
import numpy as np 
from itertools import permutations 

# Create Jobs

Jobs=list()
tasks =[[1,2,10],
        [2,2,10],
        [3,2,20],
        [4,2,20],
        [5,2,40],
        [6,2,40],
        [7,3,80]
        ]
number_tasks= 4
hyperperiod=20
Jobs = list()

for i in range(0,number_tasks):
    num_jobs=hyperperiod/tasks[i][2]
    print(num_jobs)
    for j in range (0,int(num_jobs)):
        job_name=10*(i+1)+(j+1)
        print(job_name)
        
        job_arrival =j*tasks[i][2]
        job_deadline =(j+1)*tasks[i][2]
        
        job=[job_name,tasks[i][1],job_arrival,job_deadline,i+1]
        Jobs.append(job)
print(Jobs)



# Fonction to check that the schedule is scheduleable

def schedulable(job_schedule):

    last_occurrence = np.zeros((number_tasks, 1)) # Empty variable for after
    Time = 0 # Passing time
    Wait=0 # Waitinf time 
    
    for j in job_schedule: # For each job
        name, exection_time, arrival_time, deadline,task_number = j # Get job information
        
        occurrence = name % 10    # Occurrence of the job
        
        # Check that, for example, 22 does not arrive before 21
        if occurrence - 1 == last_occurrence[task_number-1]:
            last_occurrence[task_number-1] = occurrence 
            
            if Time < arrival_time:
                Time = arrival_time  # Waiting for the task to arrive
            
            Wait += (Time - arrival_time) # Waiting time
            
            if Time + exection_time > deadline: # Check that the task has time to run
                return False # If it doesn't have the time, then the schedule is wrong.
            else : 
                Time += exection_time # If it has time, the task is done, so the time passes.
                
        else :
            return False
        
    return Wait
        




# Use the “permutations” function in the intertools library to obtain ALL possible permutations.
all_permutations= list(permutations(Jobs)) 

Valid_permutations=[]

# Variables that help build the code 
a=0 
b=0

Best_waiting_time = float('inf')
Best_schedule = []



for i in all_permutations : 
    
    if schedulable(i) == False : # I couldn't get the “if true...” condition to work, so I did the opposite.
        a+=1
        
    else :
        Valid_permutations.append(i) # Stock the right schedule
        Wait = schedulable(i) # Get the waiting time
        
        if Wait < Best_waiting_time: # If the waiting time is shorter than the last recorded time
            Best_schedule.clear() # so clear the list
            Best_waiting_time = Wait # and this time becomes the new best
            Best_schedule.append((i,Wait)) # keep the schedule in the best list.
        
        elif Wait == Best_waiting_time : # If it's the same waiting time (i.e. the best for the moment)
            b+=1
            Best_schedule.append((i,Wait)) # then keep this schedule in the list of the best.
            




















