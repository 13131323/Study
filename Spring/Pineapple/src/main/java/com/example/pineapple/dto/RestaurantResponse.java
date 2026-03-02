package com.example.pineapple.dto;

import com.example.pineapple.entity.Restaurant;
import lombok.AllArgsConstructor;
import lombok.Getter;

@Getter
@AllArgsConstructor
public class RestaurantResponse {
    private Long id;
    private String name;
    private Double rating;
    private Double lat;
    private Double lng;

    public static RestaurantResponse from(Restaurant restaurant) {
        return new RestaurantResponse(
                restaurant.getId(),
                restaurant.getName(),
                restaurant.getRating(),
                restaurant.getLocation().getY(), // 위도
                restaurant.getLocation().getX()  // 경도
        );
    }
}