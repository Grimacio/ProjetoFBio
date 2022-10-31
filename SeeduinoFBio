import biosppy
import serial
import time
import numpy
import matplotlib as mpl

# Choose sample size for each analyzed data block
# At 150 Hz, signalen of 500 corresponds to approximately 500/150 = 3.33 seconds
signalen=2000
frequency=150

# Signal contains a list of ECG values, and a list of PPG values
signal=[[],[]]


with serial.Serial('COM9', baudrate=19200, timeout=0) as arduino:
    time.sleep(signalen/frequency)
    try:
        while True:
            
            # Read Serial Line
            line=arduino.readline().decode()



            # Make sure it is sent as "ppg , ecg", some parts may be missing
            if len(line)!=0 and len(line.split(","))>1 and len(line.split(",")[0])>1 and len(line.split(",")[1])>1 and "." in line.split(",")[0] and "." in line.split(",")[1] :

                
                # Add ECG signal
                signal[0]+=[float(line.split(",")[1])]


                # Add PPG signal
                signal[1]+=[float(line.split(",")[0])]
                

            # When desired dimension "signalen" is reached, analyse this data block
            if len(signal[0])==signalen:


                # Return list of indexes within the block where R peaks were detected
                #rpeaks=biosppy.signals.ecg.engzee_segmenter(signal=signal[0], sampling_rate=150.0)[0]
                rpeaks=biosppy.signals.ecg.ecg(signal=signal[0], sampling_rate=frequency, show=False)[2]

                bvppeaks=biosppy.signals.bvp.bvp(signal=signal[1], sampling_rate=frequency, show=True)[3]
                

                # Reset signal to begin the aquisition of the next data block
                signal=[[],[]]

                for i in range(len(bvppeaks)):
                    bvppeaks[i]*=frequency
                    bvppeaks[i]=int(round(bvppeaks[i],1))
                #print(bvppeaks)
                #print("\n")
                
                try:
               
                    while rpeaks[0]>bvppeaks[0]:
                        bvppeaks=bvppeaks[1:]

                    
                    ok=False
                    while not(ok):
                        if rpeaks[1] < bvppeaks[0]:
                            rpeaks=rpeaks[1:]
                        else:
                            ok=not(ok)

                    
                    j=0
                    PTTs=[]
                    for i in range(len(rpeaks)):
                        found=False
                        begin=rpeaks[i]
                        while j < len(bvppeaks) and not(found):
                            end=bvppeaks[j]
                            if end-20>begin:
                                found=True
                                PTTs+=[(end-begin)/frequency]
                            j+=1
                    print(rpeaks)
                    print(bvppeaks)
                    print(numpy.around(numpy.mean(PTTs),4))
                except:
                    print("oops")
                time.sleep(signalen/frequency)

    except Exception as e:
        print(line)
        print(e)
        arduino.close()
        print("Comms closed")
            
            
            
            
   
