#ifndef HITABLE_LIST_H
#define HITABLE_LIST_H

#include <memory>
#include <vector>

#include "hitable.h"

class HitableList : public Hitable
{
 public:
  HitableList() {};
  bool hit (const Ray &r, double t_min, double t_max, HitRecord &rec) const override;
  void add(std::unique_ptr<Hitable> object);

  std::vector<std::unique_ptr<Hitable>> list;
};

bool HitableList::hit(const Ray &r, double t_min, double t_max, HitRecord &rec) const
{
  HitRecord temp_rec;
  bool hit_anything = false;
  double closest_so_far = t_max;
  for (auto && object : list)
  {
    if (object->hit(r, t_min, closest_so_far, temp_rec))
    {
      hit_anything = true;
      closest_so_far = temp_rec.t;
      rec = temp_rec;
    }
  }
  return hit_anything;
}

void HitableList::add(std::unique_ptr<Hitable> object) {
  list.push_back(std::move(object));
}

#endif // !HITABLE_LIST_H
