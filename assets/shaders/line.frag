// Copyright (c) 2023 Berke Umut Biricik All Rights Reserved

#version 450

layout(location = 0) out vec4 o_color;

layout(location = 0) in vec4 v_color;

void main() {
  o_color = v_color;
}
