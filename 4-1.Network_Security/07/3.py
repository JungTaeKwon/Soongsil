# 20192944 JungTaeKwon 07-3

import boto3

def compare_faces(source_image, target_image, threshold=80):
    client = boto3.client('rekognition', region_name='ap-northeast-2')

    with open(source_image, 'rb') as source:
        source_bytes = source.read()

    with open(target_image, 'rb') as target:
        target_bytes = target.read()

    response = client.compare_faces(
        SourceImage={'Bytes': source_bytes},
        TargetImage={'Bytes': target_bytes},
        SimilarityThreshold=threshold
    )

    return response['FaceMatches']

def print_similarity_results(face_matches):
    for match in face_matches:
        similarity = match['Similarity']
        print(f"[*] Face similarity: {similarity:.2f}%")

if __name__ == "__main__":
    source_image = '3-1.jpg'
    target_image = '3-2.jpg'

    face_matches = compare_faces(source_image, target_image)

    if face_matches:
        print_similarity_results(face_matches)
    else:
        print("No matches found.")
