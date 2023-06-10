# EE 327 AI Chess Bot 
# Author: Louis Wong

# Import Libraries 
import chess
import chess.engine
import boto3
import paramiko
import json
import os 

# Configure your AWS credentials and region
aws_access_key_id = 'YOUR_ACCESS_KEY'
aws_secret_access_key = 'YOUR_SECRET_ACCESS_KEY'
region_name = 'us-west-2'

# Create an AWS IoT client
iot_client = boto3.client('iot', region_name=region_name,
                          aws_access_key_id=aws_access_key_id,
                          aws_secret_access_key=aws_secret_access_key)

# Specify the EC2 instance ID
ec2_instance_id = 'lichess_server'

# Specify the AWS IoT Core topic to subscribe to
iot_topic = 'your/iot/topic'

# Retrieve the public IP address of the EC2 instance
ec2_client = boto3.client('ec2', region_name=region_name,
                          aws_access_key_id=aws_access_key_id,
                          aws_secret_access_key=aws_secret_access_key)

response = ec2_client.describe_instances(InstanceIds=[ec2_instance_id])
public_ip_address = response['Reservations'][0]['Instances'][0]['PublicIpAddress']

# Create an AWS IoT policy for the EC2 instance
policy_name = 'EC2IoTPolicy'
policy_document = '''
{
    "Version": "2012-10-17",
    "Statement": [
        {
            "Effect": "Allow",
            "Action": "iot:*",
            "Resource": "*"
        }
    ]
}
'''

iot_client.create_policy(policyName=policy_name, policyDocument=policy_document)

# Attach the policy to the EC2 instance
iot_client.attach_policy(policyName=policy_name,
                         target=ec2_instance_id)

# Create an IoT Thing for the EC2 instance
thing_name = 'EC2InstanceThing'
iot_client.create_thing(thingName=thing_name)

# Create a certificate for the EC2 instance
certificate_response = iot_client.create_keys_and_certificate(setAsActive=True)

certificate_arn = certificate_response['certificateArn']
certificate_id = certificate_response['certificateId']
certificate_pem = certificate_response['certificatePem']
private_key_pem = certificate_response['keyPair']['PrivateKey']
public_key_pem = certificate_response['keyPair']['PublicKey']

# Attach the certificate to the IoT Thing
iot_client.attach_thing_principal(thingName=thing_name, principal=certificate_arn)

# Connect to the EC2 instance via SSH
# Install the AWS IoT SDK and dependencies on the EC2 instance

# On the EC2 instance, save the certificate, private key, and root CA certificate to files
cert_file_path = '/path/to/certificate.pem.crt'
key_file_path = '/path/to/private.pem.key'
root_ca_file_path = '/path/to/root-ca.crt'

with open(cert_file_path, 'w') as cert_file:
    cert_file.write(certificate_pem)

with open(key_file_path, 'w') as key_file:
    key_file.write(private_key_pem)

# Establish an SSH connection to the EC2 instance and transfer the root CA certificate
ssh_client = paramiko.SSHClient()
ssh_client.set_missing_host_key_policy(paramiko.AutoAddPolicy())
ssh_client.connect(public_ip_address, username='ec2-user', key_filename='/path/to/ec2-instance-key.pem')

sftp_client = ssh_client.open_sftp()
sftp_client.put(root_ca_file_path, 'root-ca.crt')
sftp_client.close()

ssh_client.close()

# Subscribe the EC2 instance to the AWS IoT Core topic
response = iot_client.subscribe(
    topic=iot_topic,
    qos=1,
    target=certificate_arn
)

def main():
    # create chess engine and response
    engine = chess.engine.SimpleEngine.popen_uci(os.getcwd()+"/stockfish.avx2")
    board = chess.Board()
    print(board, "\n")

    # Wait for incoming messages
    message = iot_client.get_thing_shadow(thingName='my_thing_name')

    # Check if a message is received
    if 'payload' in message:
        player_move = process_message(message['payload'].read().decode('utf-8'))


    player = input("Choose white or black: ")
    if player == "white":
        player_input_2(board,player_move)
        print(board, "\n")
    
    while not board.is_game_over():
        # Bot's turn 
        result = engine.play(board, chess.engine.Limit(time=0.1))
        print("Bot's move: "+str(result.move))
        board.push(result.move)
        print(board, "\n")

        # Player's turn 
        message = iot_client.get_thing_shadow(thingName='my_thing_name')
        if 'payload' in message:
            player_move = process_message(message['payload'].read().decode('utf-8'))
        player_input_2(board, player_move)
        print(board, "\n")
    
    print("Winner: "+ board.outcome().winner)
    engine.quit()
    return 0

def player_input_2(board,player_move):
    board.push_san(player_move)

def player_input(board):
    print(board.legal_moves)
    player_move = input("Enter move: ")
    while chess.Move.from_uci(board.parse_san(player_move).uci()) not in board.legal_moves:
        player_move = input("Invalid move. Enter move: ")
    board.push_san(player_move)

def process_message(message):
    # This function processes the received message and performs actions based on its content
    payload = json.loads(message)
    return payload

if __name__ == '__main__':
    main()