pipeline {
    agent any

    environment {
        WIFI_SSID = credentials('wifi_ssid')
        WIFI_PASSWORD = credentials('wifi_pass')
    }

    stages {
        stage('Build firmware') {
            steps {
                script{
                    docker.build(
                        'meteo-station:latest',
                        '--build-arg WIFI_SSID=${WIFI_SSID} --build-arg WIFI_PASSWORD=${WIFI_PASS} .'
                    )}
            }
        }

        stage('Extract firmware') {
            steps {
                sh '''
                    docker create --name meteo-temp meteo-station:latest
                    docker cp meteo-temp:/workspace/.pio/build/esp32dev/firmware.bin ./firmware.bin
                    docker rm meteo-temp
                '''
            }
        }

        stage('Archive') {
            steps {
                archiveArtifacts artifacts: 'firmware.bin', fingerprint: true
            }
        }
    }

    post {
        success {
            echo 'Build successful! firmware.bin is archived.'
        }
        failure {
            echo 'Build failed!'
        }
    }


}