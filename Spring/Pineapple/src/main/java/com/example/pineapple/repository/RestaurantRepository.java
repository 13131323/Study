package com.example.pineapple.repository;

import com.example.pineapple.entity.Restaurant;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.Query;
import org.springframework.data.repository.query.Param;

import java.util.List;

public interface RestaurantRepository extends JpaRepository<Restaurant, Long> {
    // 카테고리별 식당 검색 (일식, 카페 등)
    List<Restaurant> findByCategory(String category);

    // 이름에 특정 단어가 포함된 식당 검색
    List<Restaurant> findByNameContaining(String keyword);

    @Query(value = """
        SELECT * FROM restaurant r 
        WHERE ST_X(r.location) BETWEEN :minLat AND :maxLat 
          AND ST_Y(r.location) BETWEEN :minLng AND :maxLng 
        ORDER BY r.rating DESC 
        LIMIT 5
        """, nativeQuery = true)
    List<Restaurant> findTop5InViewport(
            @Param("minLat") double minLat,
            @Param("maxLat") double maxLat,
            @Param("minLng") double minLng,
            @Param("maxLng") double maxLng
    );
}