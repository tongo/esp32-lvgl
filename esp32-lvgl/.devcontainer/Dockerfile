ARG DOCKER_TAG=release-v5.5
FROM espressif/idf:${DOCKER_TAG}

ENV LC_ALL=C.UTF-8
ENV LANG=C.UTF-8

RUN apt-get update -y && apt-get install udev -y
RUN apt-get install -y --no-install-recommends curl

RUN echo "source /opt/esp/idf/export.sh > /dev/null 2>&1" >> ~/.bashrc

ENTRYPOINT [ "/opt/esp/entrypoint.sh" ]

CMD ["/bin/bash", "-c"]

# NODE JS
RUN curl -sL https://deb.nodesource.com/setup_24.x | bash - && apt-get install -y nodejs
RUN npm i lv_font_conv -g