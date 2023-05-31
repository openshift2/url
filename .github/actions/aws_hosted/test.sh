#!/bin/bash

        # construct list of label transformations. These might not all be available or usable.
        supported_images="ubuntu-latest windows-latest"
        for i in {14..44}
        do
          new_image="ubuntu-${i}.04"
          supported_images="${supported_images} ${new_image}"
          new_image="ubuntu-${i}.10"
          supported_images="${supported_images} ${new_image}"
          new_image="windows-20${i}"
          supported_images="${supported_images} ${new_image}"
        done


echo ${supported_images}


