import boto3
import json

def detect_faces():

    client=boto3.client('rekognition')

    image=open('bp.jpeg','rb')
	
    response = client.detect_faces(Image={'Bytes':image.read()},Attributes=['ALL'])


    
    print('Detected faces')    
    for faceDetail in response['FaceDetails']:
        print (faceDetail)
        print('The detected face is between ' + str(faceDetail['AgeRange']['Low']) 
              + ' and ' + str(faceDetail['AgeRange']['High']) + ' years old')

        print('Here are the other attributes:')
        print(json.dumps(faceDetail, indent=4, sort_keys=True))

		# Access predictions for individual face details and print them
        print("Gender: " + str(faceDetail['Gender']))
        print("Smile: " + str(faceDetail['Smile']))
        print("Eyeglasses: " + str(faceDetail['Eyeglasses']))
        print("Emotions: " + str(faceDetail['Emotions'][0]))

    return len(response['FaceDetails'])

def main():
    face_count=detect_faces()
    print("Faces detected: " + str(face_count))


if __name__ == "__main__":
    main()
