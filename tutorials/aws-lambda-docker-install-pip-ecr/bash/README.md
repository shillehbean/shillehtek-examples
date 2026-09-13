# Bash examples

- [`install_aws_cli.sh`](./install_aws_cli.sh) — Download and install the AWS CLI v2 on a Linux x86_64 system.
- [`ecr_create_repo.sh`](./ecr_create_repo.sh) — Create an Amazon ECR repository named my-lambda-repo in us-east-1.
- [`ecr_docker_login.sh`](./ecr_docker_login.sh) — Authenticate Docker to the specified ECR registry using the AWS CLI get-login-password command.
- [`docker_build.sh`](./docker_build.sh) — Build the Docker image locally and tag it as my-lambda-image.
- [`docker_tag.sh`](./docker_tag.sh) — Tag the local Docker image for the target ECR repository with the account-specific registry URI.
- [`docker_push.sh`](./docker_push.sh) — Push the tagged Docker image to the target Amazon ECR repository.
- [`update_lambda_code.sh`](./update_lambda_code.sh) — Update the specified AWS Lambda function to use the image stored in ECR.

Full walkthrough: [tutorial](https://shillehtek.com/blogs/news/aws-lambda-docker-install-pip-ecr)  
Parts: [shop at shillehtek.com](https://shillehtek.com)
