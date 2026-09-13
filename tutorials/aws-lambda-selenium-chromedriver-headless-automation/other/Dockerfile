# Dockerfile that builds an AWS Lambda Python container image, installs system dependencies, runs a chrome installer script, installs Selenium, copies the application code, and sets the Lambda handler.
#
# Full tutorial: https://shillehtek.com/blogs/news/aws-lambda-selenium-chromedriver-headless-automation
# Shop parts: https://shillehtek.com
# More examples: https://github.com/shillehbean/shillehtek-examples
#

FROM amazon/aws-lambda-python:3.12

# Install chrome dependencies
RUN dnf install -y atk cups-libs gtk3 libXcomposite alsa-lib \
    libXcursor libXdamage libXext libXi libXrandr libXScrnSaver \
    libXtst pango at-spi2-atk libXt xorg-x11-server-Xvfb \
    xorg-x11-xauth dbus-glib dbus-glib-devel nss mesa-libgbm jq unzip

# Copy and run the chrome installer script
COPY ./chrome-installer.sh ./chrome-installer.sh
RUN chmod +x ./chrome-installer.sh
RUN ./chrome-installer.sh
RUN rm ./chrome-installer.sh

# Install selenium
RUN pip install selenium

# Copy the main application code
COPY main.py ./

# Command to run the Lambda function
CMD [ "main.lambda_handler" ]
